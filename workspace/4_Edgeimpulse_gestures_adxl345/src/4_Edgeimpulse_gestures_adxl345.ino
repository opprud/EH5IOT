/*
 * Project 4_Edgeimpulse_gestures_adxl345
 * Description:
 * Author:
 * Date:
 */
#include "Particle.h"
#include "ADXL345.h"
#include <Argon_gestures_inferencing.h>
//#include "../lib/Argon_gestures_inferencing/src/model-parameters/model_metadata.h"

// allow app to run before connection to cloud
SYSTEM_THREAD(ENABLED);

ADXL345 Accel;
Timer timer(20, sample_tick);

// inferencing variables
bool do_inference, first_run;
int ix;
float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

/**
 * @brief timer callback for sampling accelerometer. Read 50 x,y,z samples, and sets do_inference falg when buffer is full
 *
 */
void sample_tick(void)
{
  double acc_data[3];
  if (ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
  {
    Accel.get_Gxyz(acc_data);
    if (Accel.status)
    {
      features[ix] = acc_data[0];
      features[ix + 1] = acc_data[1];
      features[ix + 2] = acc_data[2];
      ix += 3;
    }
    else
    {
      Serial.println("ERROR: ADXL345 data read error..");
    }
  }
  // if buffer is full
  else
  {
    do_inference = 1;
    ix = 0;
    timer.stop();
  }
}

/**
 * @brief      Copy raw feature data in out_ptr
 *             Function called by inference library
 *
 * @param[in]  offset   The offset
 * @param[in]  length   The length
 * @param      out_ptr  The out pointer
 *
 * @return     0
 */
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{
  memcpy(out_ptr, features + offset, length * sizeof(float));
  return 0;
}

/**
 * @brief setup I2C, ADXL345 and serial port
 *
 */
void setup()
{
  Serial.begin(115200);
  Serial.println("Edge Impulse Inferencing Demo - MOJ Gestures example ");
  Wire.setSpeed(100000);
  Wire.begin();
  delay(5);
  Accel.powerOn();
  delay(2);
  Accel.setRangeSetting(4);
  delay(2);
  Accel.setFullResBit(1);
  delay(2);
  Accel.setJustifyBit(0);
  delay(2);
  Accel.set_bw(ADXL345_BW_100); //(ADXL345_BW_12);
  Serial.print("BW_OK? ");
  Serial.println(Accel.status, DEC);
  delay(500);
  timer.start();
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // run only once
  if (first_run)
  {
    ei_printf("Edge Impulse standalone inferencing (modified from Arduino to Particle )\n");

    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
    {
      ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
      delay(1000);
      return;
    }
    first_run = 0;
  }
  // wait for sampling to be completed
  if (do_inference)
  {
    ei_impulse_result_t result = {0};

    // the features are stored into flash, and we don't want to load everything into RAM
    signal_t features_signal;
    features_signal.total_length = sizeof(features) / sizeof(features[0]);
    features_signal.get_data = &raw_feature_get_data;

    // invoke the impulse
    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
    ei_printf("run_classifier returned: %d\n", res);

    if (res != 0)
      return;

    // print the predictions
    ei_printf("Predictions ");
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
              result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    ei_printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++)
    {
      ei_printf("%.5f", result.classification[ix].value);
#if EI_CLASSIFIER_HAS_ANOMALY == 1
      ei_printf(", ");
#else
      if (ix != EI_CLASSIFIER_LABEL_COUNT - 1)
      {
        ei_printf(", ");
      }
#endif
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("%.3f", result.anomaly);
#endif
    ei_printf("]\n");

    // human-readable predictions
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++)
    {
      ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif
    // inference_done = 1;
    do_inference = 0;
    timer.start();
  }
}