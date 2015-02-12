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
        *@brief 构造函数
        */
        Log();

        /**
        *@brief 构造函数
        *@param[in] xmlPath xml文件路径
        *@param[in] catsStr 要加载xml文件里面那些Category，如"C1,C4"；为NULL则加载xml里面指定的Category
        *@param[in] loadDef cats指定的Category在xml文件中没有找到，是否加载xml里面指定的Category
        */
        //explicit Log(const char *xmlPath, const char* catsStr, bool loadDef);

        /**
        *@brief 析构函数
        */
        ~Log();

        /**
        *@brief 级别
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
        *@brief 得到Category的实例
        *@param[in] name Category的名称
        *@return Category的实例指针
        *@retval NULL 表示没有与此名字相对应的Category
        *@retval 非NULL 表示找到对应的Category
        */
        Category* GetCategoryIns(const std::string& name) const;

        /**
        *@brief 根据xml内容自动生成Category和Appender
        *@param[in] xmlPath xml文件路径
        *@param[in] catsStr 要加载xml文件里面那些Category，如"C1,C4"；为NULL则加载xml里面指定的Category
        *@param[in] loadDef cats指定的Category在xml文件中没有找到，是否加载xml里面指定的Category
        *@return 是否成功
        *@retval false不成功；其他则成功
        */
        //bool AttachXml(const char *xmlPath, const char* catsStr, bool loadDef);

        /**
        *@brief 附加Category
        *@param[in] category Category实例的指针
        */
        void AttachCategory(Category* category);

        /**
        *@brief 用户输出字串信息(Multi-Byte)
        *@param[in] logFormat 输出信息的格式
        *@param[in] format 要输出的信息
        */
        void OutputA(const LogFormat& logFormat, char* format, ...);

        /**
        *@brief 用户输出字串信息(Unicode)
        *@param[in] logFormat 输出信息的格式
        *@param[in] format 要输出的信息
        */
        void OutputW(const LogFormat &logFormat, wchar_t *format, ...);

        /**
        *@brief 用户输出二进制数据
        *@param[in] addr 数据开始地址
        *@param[in] len 数据长度
        */
        void OutputBin(const unsigned char *addr, unsigned long len);

    protected:
        /**
        *@privatesection
        */
        /**具体实现类的实例 */
        LogAgent *log_agent_;
    };
}//base
#endif