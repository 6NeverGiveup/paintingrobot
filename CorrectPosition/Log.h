

#ifndef   _HHES_LOG_H_
#define   _HHES_LOG_H_

#include <afx.h>

/*! \brief ��־��
 *
 * �ڵ��ó�������Ŀ¼������Log�ļ���,�ڸ��ļ�����ÿ������һ����־�ļ�(��2004-07-03.log)
 * �����־�ļ��Ѿ�����1MB������պ���д�롣
 */
class CLogFile
{
public:
	/*! \brief ���캯��
     *  
	 * ����Ϊprotected����ֹ���ɸ����ʵ��
	 */
	CLogFile();

	/*! \brief ��������
     *  
	 */
	~CLogFile();

	/*! \brief д��־�ļ�
     *  
	 *  \param lpText ��־��Ϣ
	 */
	static void WriteLogFile(CString &lpText);	

protected:


	/*! \brief ��ȡ�����������ļ���·��,��"\\"��β
     *  
	 */
	static CString GetDirOfExe();

	/*! \brief �ж��ļ����Ƿ����
     *  
	 */
	static BOOL IsDirExist(const CString &strDirPath);	

	/*! \brief �ж��ļ��Ƿ����
     *  
	 */
	static BOOL IsFileExist(const CString &strFilePath);

	/*! \brief ����ļ�����1MB, ɾ!
     *  
	 */
	static void ClearLog(const CString& strFilePath);

	/*! \brief д��־
     *  
	 */
	static void WriteLog(CString& strText, const CString& strFilePath);
	
};

#endif

/*! @} */