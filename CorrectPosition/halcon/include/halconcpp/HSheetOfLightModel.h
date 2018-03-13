/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 11.0
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HSHEETOFLIGHTMODEL
#define HCPP_HSHEETOFLIGHTMODEL

namespace HalconCpp
{

// Represents an instance of the data structure required to perform 3D measurements with the sheet-of-light technique.
class LIntExport HSheetOfLightModel : public HToolBase
{

public:

  // Create an uninitialized instance
  HSheetOfLightModel():HToolBase() {}

  // Copy constructor
  HSheetOfLightModel(const HSheetOfLightModel& source) : HToolBase(source) {}

  // Create HSheetOfLightModel from handle, taking ownership
  explicit HSheetOfLightModel(Hlong handle);

  // Set new handle, taking ownership
  void SetHandle(Hlong handle);



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // create_sheet_of_light_model: Create a model to perform 3D-measurements using the sheet-of-light technique.
  explicit HSheetOfLightModel(const HRegion& ProfileRegion, const HTuple& GenParamNames, const HTuple& GenParamValues);

  // create_sheet_of_light_model: Create a model to perform 3D-measurements using the sheet-of-light technique.
  explicit HSheetOfLightModel(const HRegion& ProfileRegion, const HString& GenParamNames, Hlong GenParamValues);

  // create_sheet_of_light_model: Create a model to perform 3D-measurements using the sheet-of-light technique.
  explicit HSheetOfLightModel(const HRegion& ProfileRegion, const char* GenParamNames, Hlong GenParamValues);




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Get the result of a calibrated measurement performed with the  sheet-of-light technique as a 3D object model.
  HObjectModel3D GetSheetOfLightResultObjectModel3d() const;

  // Get the iconic results of a measurement performed with the sheet-of light technique.
  HImage GetSheetOfLightResult(const HTuple& ResultName) const;

  // Get the iconic results of a measurement performed with the sheet-of light technique.
  HImage GetSheetOfLightResult(const HString& ResultName) const;

  // Get the iconic results of a measurement performed with the sheet-of light technique.
  HImage GetSheetOfLightResult(const char* ResultName) const;

  // Apply the calibration transformations to the input disparity image.
  void ApplySheetOfLightCalibration(const HImage& Disparity) const;

  // Set sheet of light profiles by measured disparities.
  void SetProfileSheetOfLight(const HImage& ProfileDisparityImage, const HTuple& MovementPoses) const;

  // Process the profile image provided as input and store the resulting disparity to the sheet-of-light model.
  void MeasureProfileSheetOfLight(const HImage& ProfileImage, const HTuple& MovementPose) const;

  // Set selected parameters of the sheet-of-light model.
  void SetSheetOfLightParam(const HString& GenParamName, const HTuple& GenParamValue) const;

  // Set selected parameters of the sheet-of-light model.
  void SetSheetOfLightParam(const HString& GenParamName, const HString& GenParamValue) const;

  // Set selected parameters of the sheet-of-light model.
  void SetSheetOfLightParam(const char* GenParamName, const char* GenParamValue) const;

  // Get the value of a parameter, which has been set in a sheet-of-light model.
  HTuple GetSheetOfLightParam(const HString& GenParamName) const;

  // Get the value of a parameter, which has been set in a sheet-of-light model.
  HTuple GetSheetOfLightParam(const char* GenParamName) const;

  // For a given sheet-of-light model get the names of the generic iconic or control parameters that can be used in the different sheet-of-light operators.
  HTuple QuerySheetOfLightParams(const HString& QueryName) const;

  // For a given sheet-of-light model get the names of the generic iconic or control parameters that can be used in the different sheet-of-light operators.
  HTuple QuerySheetOfLightParams(const char* QueryName) const;

  // Reset a sheet-of-light model.
  void ResetSheetOfLightModel() const;

  // Create a model to perform 3D-measurements using the sheet-of-light technique.
  void CreateSheetOfLightModel(const HRegion& ProfileRegion, const HTuple& GenParamNames, const HTuple& GenParamValues);

  // Create a model to perform 3D-measurements using the sheet-of-light technique.
  void CreateSheetOfLightModel(const HRegion& ProfileRegion, const HString& GenParamNames, Hlong GenParamValues);

  // Create a model to perform 3D-measurements using the sheet-of-light technique.
  void CreateSheetOfLightModel(const HRegion& ProfileRegion, const char* GenParamNames, Hlong GenParamValues);

};

class LIntExport HSheetOfLightModelArray : public HToolArray
{
public:
  HSheetOfLightModelArray();
  HSheetOfLightModelArray(HSheetOfLightModel* classes, Hlong length);
protected:
  virtual void CreateArray(Hlong length);
};

}

#endif