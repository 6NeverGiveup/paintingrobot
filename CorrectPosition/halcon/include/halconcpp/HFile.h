/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 11.0
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HFILE
#define HCPP_HFILE

namespace HalconCpp
{

// Represents an instance of a file.
class LIntExport HFile : public HToolBase
{

public:

  // Create an uninitialized instance
  HFile():HToolBase() {}

  // Copy constructor
  HFile(const HFile& source) : HToolBase(source) {}

  // Create HFile from handle, taking ownership
  explicit HFile(Hlong handle);

  // Set new handle, taking ownership
  void SetHandle(Hlong handle);



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // open_file: Open a file in ASCII or a binary format.
  explicit HFile(const HString& FileName, const HString& FileType);

  // open_file: Open a file in ASCII or a binary format.
  explicit HFile(const char* FileName, const char* FileType);




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Open a file in ASCII or a binary format.
  void OpenFile(const HString& FileName, const HString& FileType);

  // Open a file in ASCII or a binary format.
  void OpenFile(const char* FileName, const char* FileType);

  // Write values in a file.
  void FwriteString(const HTuple& String) const;

  // Write values in a file.
  void FwriteString(const HString& String) const;

  // Write values in a file.
  void FwriteString(const char* String) const;

  // Read a line from a file.
  HString FreadLine(Hlong* IsEOF) const;

  // Read strings from a file.
  HString FreadString(Hlong* IsEOF) const;

  // Read a character from a file.
  HString FreadChar() const;

  // Create a line feed.
  void FnewLine() const;

};

class LIntExport HFileArray : public HToolArray
{
public:
  HFileArray();
  HFileArray(HFile* classes, Hlong length);
protected:
  virtual void CreateArray(Hlong length);
};

}

#endif
