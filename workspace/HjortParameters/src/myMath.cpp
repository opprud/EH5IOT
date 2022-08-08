#include "myMath.hpp"
#include <Math.h>
/**
 * @brief      The CMSIS std variance function with the same behaviour as the NumPy
 * implementation
 * @details    Variance in CMSIS version is calculated using fSum / (float)(blockSize - 1)
 * @param[in]  pSrc       Pointer to float block
 * @param[in]  blockSize  Number of floats in block
 * @param      pResult    The variance
 */
void cmsis_arm_variance(float *pSrc, uint32_t blockSize, float *pResult)
{
  uint32_t blkCnt;
  float sum = 0.0f;
  float fSum = 0.0f;
  float fMean, fValue;
  const float *pInput = pSrc;

  if (blockSize <= 1U)
  {
    *pResult = 0;
    return;
  }
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    sum += *pInput++;
    sum += *pInput++;
    sum += *pInput++;
    sum += *pInput++;
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    sum += *pInput++;
    blkCnt--;
  }

  fMean = sum / (float)blockSize;

  pInput = pSrc;

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;
    blkCnt--;
  }

  /* Variance */
  *pResult = fSum / (float)(blockSize);
}


//calculate mobility s the square root of the ratio between the  variance  of  the  first  derivative  of  the  signal  and  thevariance of the amplitude of the original signal.
float mobility(float *x, int len)
{
  float var_x = variance(x, len);
  float var_dx = variance(derivative(x, len), len);
  return sqrt(var_dx / var_x);
}

//calculate the derivative of the signal
float *derivative(float *x, int len)
{
  float *dx = new float[len];
  for (int i = 0; i < len; i++)
  {
    dx[i] = x[i + 1] - x[i];
  }
  return dx;
}

//calculate the variance of the signal
float variance(float *x, int len)
{
  float sum = 0;
  for (int i = 0; i < len; i++)
  {
    sum += x[i];
  }
  float mean = sum / len;
  float var = 0;
  for (int i = 0; i < len; i++)
  {
    var += (x[i] - mean) * (x[i] - mean);
  }
  return var / len;
}

//calculate the mean of the signal
float mean(float *x, int len)
{
  float sum = 0;
  for (int i = 0; i < len; i++)
  {
    sum += x[i];
  }
  return sum / len;
}

//calculate the standard deviation of the signal
float stdd(float *x, int len)
{
  float sum = 0;
  for (int i = 0; i < len; i++)
  {
    sum += x[i];
  }
  float mean = sum / len;
  float var = 0;
  for (int i = 0; i < len; i++)
  {
    var += (x[i] - mean) * (x[i] - mean);
  }
  return sqrt(var / len);
}

/*
    first_diff = np.diff(signal)
    first_diff_std = np.std(first_diff)
    second_diff = np.diff(first_diff)
    std = np.std(signal)
    
    activity_hjorts_parameters = std**2
    mobility_hjorts_parameters = first_diff_std/std
    complexity_hjorts_parameters = (np.std(second_diff)/first_diff_std )/ (first_diff_std / std)
    return [activity_hjorts_parameters, mobility_hjorts_parameters, complexity_hjorts_parameters]
*/