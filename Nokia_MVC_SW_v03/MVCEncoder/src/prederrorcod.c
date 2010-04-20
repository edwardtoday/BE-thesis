/* 
LIMITED LICENSE AGREEMENT

These terms (the "Terms") govern your use of the attached Nokia MVC software package (the "Code"). The Terms are an agreement (the "Agreement") between You and Nokia Corporation including its affiliates and suppliers (collectively "Nokia"). 

"You" (or "Your") shall mean an individual or legal entity exercising permissions granted by this License.

You are not allowed to use the Code if you do not agree to these Terms. You must be at least eighteen (18) years of age to accept these Terms.

 

1. LICENSE AND USE
Subject to these Terms, Nokia hereby grants to You, and you hereby accept, solely under the copyrights licensable by Nokia, a non-exclusive, worldwide, royalty-free copyright license to reproduce, use, publicly display and perform the Code, in source code, object code, and executable form, and to create derivative works of the Code solely to study, demonstrate and experiment with the H.264/MVC standard. You may redistribute or make available the Code or any derivative works thereof to any third party only pursuant to the terms of a license agreement that: (a) contains terms substantially similar to this license agreement; and (b) explicitly names Nokia as a third party beneficiary. 

This License does not grant You permission to use the trade names, trademarks, service marks, or product names of Nokia. 

This Agreement does not grant You any patent rights or other intellectual property rights, except the copyright license above. You assume sole responsibility for securing any other intellectual property rights needed. For example, if patent licenses are required, it is Your responsibility to acquire the licenses at Your own cost. To enquire about patent or other intellectual property rights licenses from Nokia, please contact Nokia Patent Licensing (Request.patentlicense@nokia.com).

2. OWNERSHIP

As between You and Nokia, Nokia retains the ownership of copyrights and all other intellectual property rights, including patent rights to the Code, as well as all Nokia trademarks, service marks, trade names, logos or other words or symbols.

3. FEEDBACK
You may, but you are not obliged to, report Your findings and results of the use of the Code to Nokia ("Feedback"). Giving Feedback to Nokia is completely voluntary. Feedback includes, without limitation, materials as well as ideas or know how (whether presented orally, in written form or otherwise).  With respect to such Feedback, You hereby grant Nokia, solely under Your copyrights, the worldwide, non-exclusive, perpetual, irrevocable, royalty-free rights  (1) to copy and modify Feedback and to create derivative works thereof, (2) to make (and have made), use, import, sell, offer for sale, lease or otherwise distribute any products or services of Nokia containing Feedback, and (3) to sublicense the foregoing rights to the extent a license is necessary for using products or services of Nokia. 

4. WARRANTIES
THE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND EXPRESS OR IMPLIED AND NEITHER NOKIA, ITS LICENSORS OR AFFILIATES NOR THE COPYRIGHT HOLDERS MAKE ANY REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR THAT THE CODE WILL NOT INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS.  THERE IS NO WARRANTY BY NOKIA OR BY ANY OTHER PARTY THAT THE FUNCTIONS CONTAINED IN THE CODE WILL MEET YOUR REQUIREMENTS OR WILL BE UNINTERRUPTED OR ERROR-FREE.  

5. LIMITATION OF LIABILITY

IN NO EVENT SHALL NOKIA, ITS EMPLOYEES OR SUPPLIERS OR AFFILIATES BE LIABLE FOR ANY LOST PROFITS, REVENUE, SALES, DATA OR COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, PROPERTY DAMAGE, PERSONAL INJURY, INTERRUPTION OF BUSINESS, LOSS OF BUSINESS INFORMATION OR FOR ANY SPECIAL, DIRECT, INDIRECT, INCIDENTAL, ECONOMIC, COVER, PUNITIVE, SPECIAL OR CONSEQUENTIAL DAMAGES, HOWEVER CAUSED AND WHETHER ARISING UNDER CONTRACT, TORT, NEGLIGENCE, OR OTHER THEORY OF LIABILITY ARISING OUT OF THE USE OF OR INABILITY TO USE THE CODE, EVEN IF NOKIA OR ITS EMPLOYEES OR SUPPLIERS OR AFFILIATES ARE ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. BECAUSE SOME COUNTRIES/STATES/ JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR LIMITATION OF LIABILITY, BUT MAY ALLOW LIABILITY TO BE LIMITED, IN SUCH CASES, NOKIA, ITS EMPLOYEES OR LICENSORS OR AFFILIATES' LIABILITY SHALL BE LIMITED TO U.S.$50. 

6. TERM AND TERMINATION
Nokia may terminate this agreement at any time. This agreement terminates automatically if You violate these Terms, if Nokia posts a notice of termination on this site, or if Nokia sends You a written notice of termination.


7. GENERAL
7.1 Indemnification

You agree to defend, indemnify and hold harmless Nokia from and against any and all third party claims either actual or threatened and all liabilities and other expenses of any kind whatsoever arising from any claim by a third party, assessments, losses, costs or damages resulting from or arising out of i) your breach of these Terms, or ii) Your use of the Code.

7.2 Governing Law and Arbitration

Except where prohibited by applicable law or provided otherwise herein, these Terms shall be governed by the laws of New York without regard to its conflicts of law provisions.  

Any dispute relating to these Terms or the Code shall be submitted to binding arbitration in Westchester County, New York within eighteen (18) months of the date the facts giving rise to the suit were known, or should have been known, by the complainant, except that Nokia may seek injunctive or other relief if you have violated or threatened to violate any intellectual property rights. All matters relating to arbitration shall be governed by the Federal Arbitration Act (9 U.S.C. �1 et. seq.). Arbitration shall be conducted by a single arbitrator under the then prevailing Wireless Arbitration Rules of the American Arbitration Association (�AAA�). Each party must submit any claim which would constitute a compulsory counterclaim in litigation or such claim shall be barred. No award of exemplary, special, consequential or punitive damages shall be permitted. The losing party, as determined by the arbitrator, shall pay the arbitration fees. The arbitrator's award shall be binding and may be entered as a judgment and enforceable in any court of competent jurisdiction. Arbitration shall be conducted on an individual, not class-wide basis, and no arbitration shall be joined with an arbitration involving any other person or entity.

7.3 Severability

If any provision contained in these Terms is determined to be invalid or unenforceable, in whole or in part, the remaining provisions and any partially enforceable provision will, nevertheless, be binding and enforceable, and the parties agree to substitute for the invalid provision a valid provision which most closely approximates the intent and economic effect of the invalid provision.

7.4 Export Control

You shall follow all export control laws and regulations relating to the Code. You agree not to export or re-export, as the case may be, the Code to any country without obtaining licenses and permits that may be required under any applicable legislation or regulations.  You shall not license the Code or provide services, nor export or re-export any information, or any process, product or service that is produced under these Terms to any country specified as a prohibited destination in applicable national, state and local, regulations and ordi�nances, including the Regulations of the U.S. Department of Commerce and/or the U.S. State Department, without first obtaining government approval.
*/

/*
 *
 * prederrorcod.c
 *
 * Contains:
 *    Functions for prediction error coding.
 *
 */

#include <string.h>
#include "globals.h"
#include "nrctypes.h"
#include "transform.h"
#include "vlcutility.h"
#include "prederrordec.h"


/*
 *
 * pecCodeBlock:
 *
 * Parameters:
 *      orig                  Original pixels for a block
 *      pred                  Predicted pixels for a block
 *      coef                  Return pointer for coefficients
 *      qp                    Quantization parameter
 *      picType               Type of picture (intra/inter)
 *
 * Function:
 *      Compute prediction error block, transform it and quantize coefficients
 *
 * Returns:
 *      Number of nonzero coefficients
 */
int pecCodeBlock(u_int8 orig[BLK_SIZE][MBK_SIZE],
                 u_int8 pred[BLK_SIZE][MBK_SIZE],
                 int coef[BLK_SIZE][BLK_SIZE],
                 int skip,
                 int qp, 
                 int picType)
{
  int nonZero;


  /* 4x4 DCT */
  traDiffDCT4x4(orig, pred, coef);

  /* Normal quantization */

  // in JM, quantization for intra16x16 is handled as in an I-frame
  nonZero = traQuant4x4(&coef[0][0], skip, qp, picType);

  return nonZero;
}


/*
 *
 * pecCodeMB:
 *
 * Parameters:
 *      mb                    Macroblock structure
 *      picType               Type of picture (intra/inter)
 *
 * Function:
 *      Transform and quantize prediction error of all luma blocks in MB
 *
 * Returns:
 *      -
 */
void pecCodeLumaMB(macroblock_s *pMb, 
                   u_int8 pred[MBK_SIZE][MBK_SIZE],
                   int skip,
                   int picType)
{
  int coefQ[BLK_SIZE*BLK_SIZE];
  int mbCoefCost, coefCost;
  int mbNonZeros, blk8x8NonZeros;
  int blk8x8, blkIdx;
  int nonZero;

  
  pMb->cbpY = 0;

  /*
   * Luma AC DCT & quantization
   */
  mbCoefCost = 0;  /* Set MB coef cost to zero */
  mbNonZeros = 0;

  for (blk8x8 = 0; blk8x8 < 16; blk8x8 += 4) {
    coefCost = 0;  /* Set 8x8 block coef cost to zero */
    blk8x8NonZeros = 0;

    for (blkIdx = blk8x8; blkIdx < (blk8x8 + 4); blkIdx ++) {
      int blkX, blkY;

      blkX = blkRasterOrder[blkIdx] & 3;
      blkY = blkRasterOrder[blkIdx] >> 2;

      nonZero = pecCodeBlock(
        (u_int8 (*) [MBK_SIZE]) & pMb->origY[blkY * BLK_SIZE][blkX * BLK_SIZE],
        (u_int8 (*) [MBK_SIZE]) & pred[blkY * BLK_SIZE][blkX * BLK_SIZE],
        pMb->coefY[blkIdx],
        skip, pMb->qp, picType);

      // record DC coefficient anyway
      pMb->dcCoefY[blkY][blkX] = pMb->coefY[blkIdx][0][0];

      if (nonZero) {
        // Update luma CBP
        pMb->cbpY |= (unsigned int)1 << blkIdx;

        if (pMb->coeffElim) {
          blk8x8NonZeros += nonZero;
          vlcuZigZagScan4x4(pMb->coefY[blkIdx], coefQ);
          coefCost += traGetCoefCost(coefQ + skip, nonZero);
        }
      }
    }

    /* Set INTER 8x8 block to zero if coefficient cost */
    /* for block is below threshold                    */
    if (pMb->coeffElim) {
      if (coefCost <= pMb->coeffElimTh8x8 && blk8x8NonZeros > 0) {
        blk8x8NonZeros = 0;
        pMb->cbpY &= ~(0x0F << blk8x8);
        memset(pMb->coefY[blk8x8], 0, 4 * BLK_SIZE * BLK_SIZE * sizeof(int));
      }

      mbCoefCost += coefCost;
      mbNonZeros += blk8x8NonZeros;
    }
  }

  /* Set INTER MB to zero, if coefficient cost for MB is below threshold */
  if (pMb->coeffElim) {
    if (mbCoefCost <= pMb->coeffElimThLuma && mbNonZeros > 0) {
      memset(pMb->coefY, 0, MBK_SIZE*MBK_SIZE*sizeof(int));
      pMb->cbpY = 0;
    }
  }

  /*
   * Transform and quantize luma DC (if 16x16 intra mode)
   */
  pMb->lumaNonzeroDC = 0;
  if (skip) {
    /* 4x4 DC DCT */
    traHada4x4(pMb->dcCoefY);

    /* Quant */

    // DBG, check the second from the last parameter, different for luma and chroma
    pMb->lumaNonzeroDC = traQuantDC
      (& pMb->dcCoefY[0][0], pMb->qp, picType, BLK_PER_MB*BLK_PER_MB, 0);
  }
}


/*
 *
 * pecCodeChromaMB:
 *
 * Parameters:
 *      pMb                   Macroblock structure
 *      picType               Type of picture (intra/inter)
 *
 * Function:
 *      Transform and quantize prediction error of all chroma blocks in MB
 *
 * Returns:
 *      -
 */
void pecCodeChromaMB(macroblock_s *pMb, 
                     u_int8 predC[MBK_SIZE/2][2*(MBK_SIZE/2)],
                     int picType)
{
  int comp, blkIdxX, blkIdxY;
  int coefQ[BLK_SIZE*BLK_SIZE];
  int mbCoefCost;
  int totalNonZero;
  int nonZero;
  unsigned int cbpBit;

  
  pMb->cbpChromaDC = pMb->cbpC = 0;
  cbpBit = 1;

  for (comp = 0; comp < 2; comp++) {

    /*
     * Chroma AC transform and quantization
     */
    mbCoefCost = 0;  /* Set MB coef cost to zero */

    totalNonZero = 0;
    for (blkIdxY = 0; blkIdxY < BLK_PER_MB/2; blkIdxY ++) {
      for (blkIdxX = 0; blkIdxX < BLK_PER_MB/2; blkIdxX ++) {

        nonZero = pecCodeBlock(
          (u_int8 (*) [MBK_SIZE]) & pMb->origC[blkIdxY*BLK_SIZE][comp*(MBK_SIZE/2)+blkIdxX*BLK_SIZE],
          (u_int8 (*) [MBK_SIZE]) & predC[blkIdxY*BLK_SIZE][comp*(MBK_SIZE/2)+blkIdxX*BLK_SIZE],
          pMb->coefC[comp][blkIdxY][blkIdxX], 1, pMb->qpC, picType);

        /* Take DC coef out */
        pMb->dcCoefC[comp][blkIdxY][blkIdxX] = 
          pMb->coefC[comp][blkIdxY][blkIdxX][0][0];

        if (nonZero)
        {
          if (pMb->coeffElim)
          {
            totalNonZero += nonZero;
            vlcuZigZagScan4x4(pMb->coefC[comp][blkIdxY][blkIdxX], coefQ);
            mbCoefCost += traGetCoefCost(coefQ + 1, nonZero);
          }

          pMb->cbpC |= cbpBit;
        }

        cbpBit <<= 1;
      }
    }

    /* Set INTER Chroma MB to zero, if coefficient cost for MB is below threshold */
    if ((pMb->coeffElim) && (mbCoefCost <= pMb->coeffElimThChroma) && (totalNonZero > 0))
    {
      unsigned int cbpMask;

      cbpMask = (1 << (BLK_PER_MB/2*BLK_PER_MB/2)) - 1;
      pMb->cbpC &= ~(cbpMask << (comp*(BLK_PER_MB/2*BLK_PER_MB/2)));
      memset(pMb->coefC[comp], 0, MBK_SIZE/2*MBK_SIZE/2*sizeof(int));
    }

    /*
     * Chroma DC transform and quantization
     */

    /* 2x2 DC DCT */
    traDCT2x2(pMb->dcCoefC[comp]);

    /* 2x2 DC quant */

    // DBG treat chroma and luma differently
    nonZero = traQuantDC(& pMb->dcCoefC[comp][0][0], 
                         pMb->qpC, picType, BLK_PER_MB/2*BLK_PER_MB/2, 1);

    /* Update chroma CBP */
    if (nonZero)
      pMb->cbpChromaDC |= 1 << comp;
  }
}
