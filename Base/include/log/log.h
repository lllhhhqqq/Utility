/** 
 * @file log.h
 * @brief 
 * @author Luhaoqing 
 * @date 2013/11/20
*/
#ifndef LOG_H
#define LOG_H

#include <string>

namespace base {
	
    class Category;
    class LogAgent;
    class LogFormat;
    //
    class Log
    {
    public:
        /**
        *@brief ���캯��
        */
        Log();

        /**
        *@brief ���캯��
        *@param[in] xmlPath xml�ļ�·��
        *@param[in] catsStr Ҫ����xml�ļ�������ЩCategory����"C1,C4"��ΪNULL�����xml����ָ����Category
        *@param[in] loadDef catsָ����Category��xml�ļ���û���ҵ����Ƿ����xml����ָ����Category
        */
        //explicit Log(const char *xmlPath, const char* catsStr, bool loadDef);

        /**
        *@brief ��������
        */
        ~Log();

        /**
        *@brief ����
        */
        enum Level
        {
            Debug = 0,
            Msg,
            Warning,
            System,
            Err,
        };

        /**
        *@brief �õ�Category��ʵ��
        *@param[in] name Category������
        *@return Category��ʵ��ָ��
        *@retval NULL ��ʾû������������Ӧ��Category
        *@retval ��NULL ��ʾ�ҵ���Ӧ��Category
        */
        Category* GetCategoryIns(const std::string& name) const;

        /**
        *@brief ����xml�����Զ�����Category��Appender
        *@param[in] xmlPath xml�ļ�·��
        *@param[in] catsStr Ҫ����xml�ļ�������ЩCategory����"C1,C4"��ΪNULL�����xml����ָ����Category
        *@param[in] loadDef catsָ����Category��xml�ļ���û���ҵ����Ƿ����xml����ָ����Category
        *@return �Ƿ�ɹ�
        *@retval false���ɹ���������ɹ�
        */
        //bool AttachXml(const char *xmlPath, const char* catsStr, bool loadDef);

        /**
        *@brief ����Category
        *@param[in] category Categoryʵ����ָ��
        */
        void AttachCategory(Category* category);

        /**
        *@brief �û�����ִ���Ϣ(Multi-Byte)
        *@param[in] logFormat �����Ϣ�ĸ�ʽ
        *@param[in] format Ҫ�������Ϣ
        */
        void OutputA(const LogFormat& logFormat, char* format, ...);

        /**
        *@brief �û�����ִ���Ϣ(Unicode)
        *@param[in] logFormat �����Ϣ�ĸ�ʽ
        *@param[in] format Ҫ�������Ϣ
        */
        void OutputW(const LogFormat &logFormat, wchar_t *format, ...);

        /**
        *@brief �û��������������
        *@param[in] addr ���ݿ�ʼ��ַ
        *@param[in] len ���ݳ���
        */
        void OutputBin(const unsigned char *addr, unsigned long len);

    protected:
        /**
        *@privatesection
        */
        /**����ʵ�����ʵ�� */
        LogAgent *log_agent_;
    };
}//base
#endif