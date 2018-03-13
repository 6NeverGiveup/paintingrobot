/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 11.0
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HPOSE
#define HCPP_HPOSE

namespace HalconCpp
{

// Represents a rigid 3D transformation with 7 parameters (3 for the rotation, 3 for the translation, 1 for the representation type).
class LIntExport HPose : public HDataBase
{

public:

  // Create an uninitialized instance
  HPose():HDataBase() {}

  // Copy constructor
  HPose(const HPose& source) : HDataBase(source) {}

  // Deep copy of all data represented by this object instance
  HPose Clone() const;



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // create_pose: Create a 3D pose.
  explicit HPose(double TransX, double TransY, double TransZ, double RotX, double RotY, double RotZ, const HString& OrderOfTransform, const HString& OrderOfRotation, const HString& ViewOfTransform);

  // create_pose: Create a 3D pose.
  explicit HPose(double TransX, double TransY, double TransZ, double RotX, double RotY, double RotZ, const char* OrderOfTransform, const char* OrderOfRotation, const char* ViewOfTransform);


/*****************************************************************************
 * Operator overloads
 *****************************************************************************/

  // Convert to matrix
  operator HHomMat3D() const;


  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Compute the average of a set of poses.
  static HPose PoseAverage(const HPoseArray& Poses, const HTuple& Weights, const HString& Mode, const HTuple& SigmaT, const HTuple& SigmaR, HTuple* Quality);

  // Compute the average of a set of poses.
  static HPose PoseAverage(const HPoseArray& Poses, const HTuple& Weights, const HString& Mode, double SigmaT, double SigmaR, HTuple* Quality);

  // Compute the average of a set of poses.
  static HPose PoseAverage(const HPoseArray& Poses, const HTuple& Weights, const char* Mode, double SigmaT, double SigmaR, HTuple* Quality);

  // Invert each pose in a tuple of 3D poses.
  static HPoseArray PoseInvert(const HPoseArray& Pose);

  // Invert each pose in a tuple of 3D poses.
  HPose PoseInvert() const;

  // Combine 3D poses given in two tuples.
  static HPoseArray PoseCompose(const HPoseArray& PoseLeft, const HPoseArray& PoseRight);

  // Combine 3D poses given in two tuples.
  HPose PoseCompose(const HPose& PoseRight) const;

  // Compute the distance values for a rectified stereo image pair using multigrid methods.
  HImage BinocularDistanceMg(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, double GrayConstancy, double GradientConstancy, double Smoothness, double InitialGuess, const HString& CalculateScore, const HTuple& MGParamName, const HTuple& MGParamValue) const;

  // Compute the distance values for a rectified stereo image pair using multigrid methods.
  HImage BinocularDistanceMg(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, double GrayConstancy, double GradientConstancy, double Smoothness, double InitialGuess, const HString& CalculateScore, const HString& MGParamName, const HString& MGParamValue) const;

  // Compute the distance values for a rectified stereo image pair using multigrid methods.
  HImage BinocularDistanceMg(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, double GrayConstancy, double GradientConstancy, double Smoothness, double InitialGuess, const char* CalculateScore, const char* MGParamName, const char* MGParamValue) const;

  // Compute the fundamental matrix from the relative orientation of two cameras.
  HHomMat2D RelPoseToFundamentalMatrix(const HTuple& CovRelPose, const HTuple& CamPar1, const HTuple& CamPar2, HTuple* CovFMat) const;

  // Compute the relative orientation between two cameras given image point correspondences and known camera parameters and reconstruct 3D space points.
  HTuple VectorToRelPose(const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CovRR1, const HTuple& CovRC1, const HTuple& CovCC1, const HTuple& CovRR2, const HTuple& CovRC2, const HTuple& CovCC2, const HTuple& CamPar1, const HTuple& CamPar2, const HString& Method, HTuple* Error, HTuple* X, HTuple* Y, HTuple* Z, HTuple* CovXYZ);

  // Compute the relative orientation between two cameras given image point correspondences and known camera parameters and reconstruct 3D space points.
  HTuple VectorToRelPose(const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CovRR1, const HTuple& CovRC1, const HTuple& CovCC1, const HTuple& CovRR2, const HTuple& CovRC2, const HTuple& CovCC2, const HTuple& CamPar1, const HTuple& CamPar2, const HString& Method, double* Error, HTuple* X, HTuple* Y, HTuple* Z, HTuple* CovXYZ);

  // Compute the relative orientation between two cameras given image point correspondences and known camera parameters and reconstruct 3D space points.
  HTuple VectorToRelPose(const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CovRR1, const HTuple& CovRC1, const HTuple& CovCC1, const HTuple& CovRR2, const HTuple& CovRC2, const HTuple& CovCC2, const HTuple& CamPar1, const HTuple& CamPar2, const char* Method, double* Error, HTuple* X, HTuple* Y, HTuple* Z, HTuple* CovXYZ);

  // Compute the relative orientation between two cameras by automatically finding correspondences between image points.
  HTuple MatchRelPoseRansac(const HImage& Image1, const HImage& Image2, const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CamPar1, const HTuple& CamPar2, const HString& GrayMatchMethod, Hlong MaskSize, Hlong RowMove, Hlong ColMove, Hlong RowTolerance, Hlong ColTolerance, const HTuple& Rotation, const HTuple& MatchThreshold, const HString& EstimationMethod, const HTuple& DistanceThreshold, Hlong RandSeed, HTuple* Error, HTuple* Points1, HTuple* Points2);

  // Compute the relative orientation between two cameras by automatically finding correspondences between image points.
  HTuple MatchRelPoseRansac(const HImage& Image1, const HImage& Image2, const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CamPar1, const HTuple& CamPar2, const HString& GrayMatchMethod, Hlong MaskSize, Hlong RowMove, Hlong ColMove, Hlong RowTolerance, Hlong ColTolerance, double Rotation, Hlong MatchThreshold, const HString& EstimationMethod, double DistanceThreshold, Hlong RandSeed, double* Error, HTuple* Points1, HTuple* Points2);

  // Compute the relative orientation between two cameras by automatically finding correspondences between image points.
  HTuple MatchRelPoseRansac(const HImage& Image1, const HImage& Image2, const HTuple& Rows1, const HTuple& Cols1, const HTuple& Rows2, const HTuple& Cols2, const HTuple& CamPar1, const HTuple& CamPar2, const char* GrayMatchMethod, Hlong MaskSize, Hlong RowMove, Hlong ColMove, Hlong RowTolerance, Hlong ColTolerance, double Rotation, Hlong MatchThreshold, const char* EstimationMethod, double DistanceThreshold, Hlong RandSeed, double* Error, HTuple* Points1, HTuple* Points2);

  // Compute the distance values for a rectified stereo image pair using correlation techniques.
  HImage BinocularDistance(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, const HString& Method, Hlong MaskWidth, Hlong MaskHeight, const HTuple& TextureThresh, Hlong MinDisparity, Hlong MaxDisparity, Hlong NumLevels, const HTuple& ScoreThresh, const HTuple& Filter, const HTuple& SubDistance) const;

  // Compute the distance values for a rectified stereo image pair using correlation techniques.
  HImage BinocularDistance(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, const HString& Method, Hlong MaskWidth, Hlong MaskHeight, double TextureThresh, Hlong MinDisparity, Hlong MaxDisparity, Hlong NumLevels, double ScoreThresh, const HString& Filter, const HString& SubDistance) const;

  // Compute the distance values for a rectified stereo image pair using correlation techniques.
  HImage BinocularDistance(const HImage& Image1, const HImage& Image2, HImage* Score, const HTuple& CamParamRect1, const HTuple& CamParamRect2, const char* Method, Hlong MaskWidth, Hlong MaskHeight, double TextureThresh, Hlong MinDisparity, Hlong MaxDisparity, Hlong NumLevels, double ScoreThresh, const char* Filter, const char* SubDistance) const;

  // Transform a disparity image into 3D points in a rectified stereo system.
  HImage DisparityImageToXyz(const HImage& Disparity, HImage* Y, HImage* Z, const HTuple& CamParamRect1, const HTuple& CamParamRect2) const;

  // Transform an image point and its disparity into a 3D point in a rectified stereo system.
  void DisparityToPoint3d(const HTuple& CamParamRect1, const HTuple& CamParamRect2, const HTuple& Row1, const HTuple& Col1, const HTuple& Disparity, HTuple* X, HTuple* Y, HTuple* Z) const;

  // Transform an image point and its disparity into a 3D point in a rectified stereo system.
  void DisparityToPoint3d(const HTuple& CamParamRect1, const HTuple& CamParamRect2, double Row1, double Col1, double Disparity, double* X, double* Y, double* Z) const;

  // Transform a disparity value into a distance value in a rectified binocular stereo system.
  HTuple DisparityToDistance(const HTuple& CamParamRect1, const HTuple& CamParamRect2, const HTuple& Disparity) const;

  // Transform a disparity value into a distance value in a rectified binocular stereo system.
  double DisparityToDistance(const HTuple& CamParamRect1, const HTuple& CamParamRect2, double Disparity) const;

  // Transfrom a distance value into a disparity in a rectified stereo system.
  HTuple DistanceToDisparity(const HTuple& CamParamRect1, const HTuple& CamParamRect2, const HTuple& Distance) const;

  // Transfrom a distance value into a disparity in a rectified stereo system.
  double DistanceToDisparity(const HTuple& CamParamRect1, const HTuple& CamParamRect2, double Distance) const;

  // Generate transformation maps that describe the mapping of the images of a binocular camera pair to a common rectified image plane.
  HImage GenBinocularRectificationMap(HImage* Map2, const HTuple& CamParam1, const HTuple& CamParam2, double SubSampling, const HString& Method, const HString& MapType, HTuple* CamParamRect1, HTuple* CamParamRect2, HPose* CamPoseRect1, HPose* CamPoseRect2, HPose* RelPoseRect) const;

  // Generate transformation maps that describe the mapping of the images of a binocular camera pair to a common rectified image plane.
  HImage GenBinocularRectificationMap(HImage* Map2, const HTuple& CamParam1, const HTuple& CamParam2, double SubSampling, const char* Method, const char* MapType, HTuple* CamParamRect1, HTuple* CamParamRect2, HPose* CamPoseRect1, HPose* CamPoseRect2, HPose* RelPoseRect) const;

  // Determine all camera parameters of a binocular stereo system.
  static HTuple BinocularCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow1, const HTuple& NCol1, const HTuple& NRow2, const HTuple& NCol2, const HTuple& StartCamParam1, const HTuple& StartCamParam2, const HPoseArray& NStartPose1, const HPoseArray& NStartPose2, const HTuple& EstimateParams, HTuple* CamParam2, HPoseArray* NFinalPose1, HPoseArray* NFinalPose2, HPose* RelPose, HTuple* Errors);

  // Determine all camera parameters of a binocular stereo system.
  HTuple BinocularCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow1, const HTuple& NCol1, const HTuple& NRow2, const HTuple& NCol2, const HTuple& StartCamParam1, const HTuple& StartCamParam2, const HPose& NStartPose2, const HString& EstimateParams, HTuple* CamParam2, HPose* NFinalPose1, HPose* NFinalPose2, HPose* RelPose, double* Errors) const;

  // Determine all camera parameters of a binocular stereo system.
  HTuple BinocularCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow1, const HTuple& NCol1, const HTuple& NRow2, const HTuple& NCol2, const HTuple& StartCamParam1, const HTuple& StartCamParam2, const HPose& NStartPose2, const char* EstimateParams, HTuple* CamParam2, HPose* NFinalPose1, HPose* NFinalPose2, HPose* RelPose, double* Errors) const;

  // Create a 3D camera pose from camera center and viewing direction.
  void CreateCamPoseLookAtPoint(const HTuple& CamPosX, const HTuple& CamPosY, const HTuple& CamPosZ, const HTuple& LookAtX, const HTuple& LookAtY, const HTuple& LookAtZ, const HTuple& RefPlaneNormal, const HTuple& CamRoll);

  // Create a 3D camera pose from camera center and viewing direction.
  void CreateCamPoseLookAtPoint(double CamPosX, double CamPosY, double CamPosZ, double LookAtX, double LookAtY, double LookAtZ, const HString& RefPlaneNormal, double CamRoll);

  // Create a 3D camera pose from camera center and viewing direction.
  void CreateCamPoseLookAtPoint(double CamPosX, double CamPosY, double CamPosZ, double LookAtX, double LookAtY, double LookAtZ, const char* RefPlaneNormal, double CamRoll);

  // Transform a pose that refers to the coordinate system of a 3D object model to a pose that refers to the reference coordinate system of a 3D shape model and vice versa.
  HPose TransPoseShapeModel3d(const HShapeModel3D& ShapeModel3DID, const HString& Transformation) const;

  // Transform a pose that refers to the coordinate system of a 3D object model to a pose that refers to the reference coordinate system of a 3D shape model and vice versa.
  HPose TransPoseShapeModel3d(const HShapeModel3D& ShapeModel3DID, const char* Transformation) const;

  // Generate a projection map that describes the mapping between the image plane and a the plane z=0 of a world coordinate system.
  HImage GenImageToWorldPlaneMap(const HTuple& CameraParam, Hlong WidthIn, Hlong HeightIn, Hlong WidthMapped, Hlong HeightMapped, const HTuple& Scale, const HString& MapType) const;

  // Generate a projection map that describes the mapping between the image plane and a the plane z=0 of a world coordinate system.
  HImage GenImageToWorldPlaneMap(const HTuple& CameraParam, Hlong WidthIn, Hlong HeightIn, Hlong WidthMapped, Hlong HeightMapped, const HString& Scale, const HString& MapType) const;

  // Generate a projection map that describes the mapping between the image plane and a the plane z=0 of a world coordinate system.
  HImage GenImageToWorldPlaneMap(const HTuple& CameraParam, Hlong WidthIn, Hlong HeightIn, Hlong WidthMapped, Hlong HeightMapped, const char* Scale, const char* MapType) const;

  // Transform an XLD contour into the plane z=0 of a world coordinate system.
  HXLDCont ContourToWorldPlaneXld(const HXLDCont& Contours, const HTuple& CameraParam, const HTuple& Scale) const;

  // Transform an XLD contour into the plane z=0 of a world coordinate system.
  HXLDCont ContourToWorldPlaneXld(const HXLDCont& Contours, const HTuple& CameraParam, const HString& Scale) const;

  // Transform an XLD contour into the plane z=0 of a world coordinate system.
  HXLDCont ContourToWorldPlaneXld(const HXLDCont& Contours, const HTuple& CameraParam, const char* Scale) const;

  // Translate the origin of a 3D pose.
  HPose SetOriginPose(double DX, double DY, double DZ) const;

  // Perform a hand-eye calibration.
  static HPose HandEyeCalibration(const HTuple& X, const HTuple& Y, const HTuple& Z, const HTuple& Row, const HTuple& Col, const HTuple& NumPoints, const HPoseArray& RobotPoses, const HTuple& CameraParam, const HString& Method, const HTuple& QualityType, HPose* CalibrationPose, HTuple* Quality);

  // Perform a hand-eye calibration.
  static HPose HandEyeCalibration(const HTuple& X, const HTuple& Y, const HTuple& Z, const HTuple& Row, const HTuple& Col, const HTuple& NumPoints, const HPoseArray& RobotPoses, const HTuple& CameraParam, const HString& Method, const HString& QualityType, HPose* CalibrationPose, double* Quality);

  // Perform a hand-eye calibration.
  static HPose HandEyeCalibration(const HTuple& X, const HTuple& Y, const HTuple& Z, const HTuple& Row, const HTuple& Col, const HTuple& NumPoints, const HPoseArray& RobotPoses, const HTuple& CameraParam, const char* Method, const char* QualityType, HPose* CalibrationPose, double* Quality);

  // Get the representation type of a 3D pose.
  HString GetPoseType(HString* OrderOfRotation, HString* ViewOfTransform) const;

  // Change the representation type of a 3D pose.
  HPose ConvertPoseType(const HString& OrderOfTransform, const HString& OrderOfRotation, const HString& ViewOfTransform) const;

  // Change the representation type of a 3D pose.
  HPose ConvertPoseType(const char* OrderOfTransform, const char* OrderOfRotation, const char* ViewOfTransform) const;

  // Create a 3D pose.
  void CreatePose(double TransX, double TransY, double TransZ, double RotX, double RotY, double RotZ, const HString& OrderOfTransform, const HString& OrderOfRotation, const HString& ViewOfTransform);

  // Create a 3D pose.
  void CreatePose(double TransX, double TransY, double TransZ, double RotX, double RotY, double RotZ, const char* OrderOfTransform, const char* OrderOfRotation, const char* ViewOfTransform);

  // Convert internal camera parameters and a 3D pose into a 3�4 projection matrix.
  HHomMat3D CamParPoseToHomMat3d(const HTuple& CameraParam) const;

  // Convert a 3D pose into a homogeneous transformation matrix.
  HHomMat3D PoseToHomMat3d() const;

  // Deserialize a serialized pose.
  void DeserializePose(const HSerializedItem& SerializedItemHandle);

  // Serialize a pose.
  HSerializedItem SerializePose() const;

  // Read a 3D pose from a text file.
  void ReadPose(const HString& PoseFile);

  // Read a 3D pose from a text file.
  void ReadPose(const char* PoseFile);

  // Write a 3D pose to a text file.
  void WritePose(const HString& PoseFile) const;

  // Write a 3D pose to a text file.
  void WritePose(const char* PoseFile) const;

  // Determine all camera parameters by a simultaneous minimization process.
  static HTuple CameraCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow, const HTuple& NCol, const HTuple& StartCamParam, const HPoseArray& NStartPose, const HTuple& EstimateParams, HPoseArray* NFinalPose, HTuple* Errors);

  // Determine all camera parameters by a simultaneous minimization process.
  HTuple CameraCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow, const HTuple& NCol, const HTuple& StartCamParam, const HString& EstimateParams, HPose* NFinalPose, double* Errors) const;

  // Determine all camera parameters by a simultaneous minimization process.
  HTuple CameraCalibration(const HTuple& NX, const HTuple& NY, const HTuple& NZ, const HTuple& NRow, const HTuple& NCol, const HTuple& StartCamParam, const char* EstimateParams, HPose* NFinalPose, double* Errors) const;

};

class LIntExport HPoseArray : public HDataArray
{
public:
  HPoseArray();
  HPoseArray(HPose* classes, Hlong length);
protected:
  virtual void CreateArray(Hlong length);
  virtual int GetFixedSize();
};

}

#endif
