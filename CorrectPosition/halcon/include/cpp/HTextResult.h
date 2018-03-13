/*****************************************************************************
 * HTextResult.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Class HTextResult
 *
 * (c) 2009-2012 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.2 $
 * $Date: 2012/04/27 13:16:35 $
 *
 */

#ifndef H_TEXT_RESULT_H
#define H_TEXT_RESULT_H


#include "HCPPToolRef.h"


namespace Halcon {


class LIntExport HTextResult: public HToolBase 
{
  
public:

  // Tool-specific functional class constructors

  HTextResult(const Halcon::HImage &Image,
              const Halcon::HTextModel &TextModel);

  // Common tool class management functionality

  HTextResult();
  HTextResult(Hlong ID);
  const char *ClassName(void) const;
  void  SetHandle(Hlong ID);

  // Tool-specific member functions

  // Clear all text results.
  static void ClearAllTextResults(void);
  // Query a control value of a text segmentation result.
  virtual HTuple GetTextResult(const Halcon::HTuple &ResultName) const;
  // Segment text in an image.
  virtual void FindText(const HImage &Image, const Halcon::HTextModel &TextModel);
};

}

#endif
