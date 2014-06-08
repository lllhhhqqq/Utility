/** 
 * @file table.h
 * @brief ��̬���ݽṹtable��ʹ��
 * @author Gliu
 * @date 09/10/2012
 * ��Ҫʹ��table���ж��塢������ʹ�õȲ�����
 *
 */

#ifndef TABLE_H_V1_0
#define TABLE_H_V1_0

//#include "dzh_base/include/dzh_base_export.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TABLE_API
	#define TABLE_API DZH_BASE_API
#define DZH_BASE_API
#endif

/** \mainpage
 *
 * C�����У��ṹ�Ƕ�һЩ�����������͵���ϣ�ͨ�� struct �ؼ��֣���������ϵ�
 * �߼��ṹ���ڱ���ʱ��������������λ�ֶε�ƫ�ƣ��Դˣ�ʹ�����ǿ��Ա�д����
 * ĳһ�ֶεĴ��롣����һЩ����£��Խṹ�Ĵ������ʣ���Ҫ������ʱ���ܾ�����
 * ��ʱ����Ҫһ�ֶ�̬�Ľṹ��
 *
 *
 * table��������һ�ֶ�̬�ṹ����C�ṹ���ƣ�ʹ��table��Ϊ���塢������ʹ�õȲ��衣
 * \section sec_create ����
 * ��һ����K�ߵ���������Ϊ����
 * \code
 * struct Day{
 *     long long   date;
 *     float open;
 *     float high;
 *     float low;
 *     float close;
 *     char  extend[64];	// ��չ����
 * };
 * \endcode
 * ͨ�����Ͷ����ַ���
 * \code
 * const char * day_schema = "date:q;open:f;high:f;low:f;close:f;extend:64c";
 * \endcode
 * ���Զ���һ����ͬ���������ݽṹ��
 *
 * ��C�����У�ͨ�� new/delete �ؼ��ֻ� malloc/free �������ṹ
 * \code
 * Day * days = new Day[100];
 * ...
 * delete [] days;
 * \endcode
 * ����table��ͨ�� table_create/table_destory ����
 * \code
 * table_t days = table_create(day_schema, 100, "days");
 * ...
 * table_destory(days);
 * \endcode
 * \section sec_schema ��������
 * �������Ե���������:
 * \code
 * table_schema    = name:[count]type[{;name:[count]type}]
 * name            = �ַ���
 * count           = ����
 * type            = c|h|i|q|f|d|s|t|C|H|I|Q|b|T|p
 * ������������ǰ��ѡ�������־��>������ <��������
 * \endcode
 * \section sec_example һ������������
 * \code
 * #include "table.h"
 * int main(){
 *     const char * day_schema = "date:q;open:f;high:f;low:f;close:f;extend:64c";
 *     table_t days = table_create(day_schema, 100, "");
 *     size_t rows = table_rows(days);
 *     size_t date_col = table_col_index("date");
 *
 *     // set date with recent 100 days
 *     time_t begin = 1337576660;
 *     for(size_t row = 0; row < rows; row++){
 *         table_set_int64(row, date_col, begin - 86400 * row);
 *         ...
 *     }
 *
 *     // print days
 *     for(size_t row = 0; row < rows; row++){
 *         printf("%I64d\n", table_get_int64(row, date_col);
 *         ...
 *     }
 *     table_destory(days);
 * }
 * \endcode
 * \section sec_thread �̰߳�ȫ
 * table \em ���� �̰߳�ȫ�ģ���һ��������һ��ͨ����ָ�룬���ϣ�����̼߳乲��
 * ��ô����������Ҫ���������Ĳ�����
 * \section sec_memory �ڴ������ַ���
 * tableʵ���У������ڲ��ڴ��ͨ�� table_strnew �����룬ͨ�� table_strdel ���ͷţ����ԣ�
 * ����Ҫ��һ���ַ������ݵ� table �ڲ�ʱ��Ҳͬ����Ҫ table_strnew �����з����ڴ棬���磬\ref table_set_str_raw
 */



 /**
  * @file table.h
  * @brief table �Ķ���ͷ�ļ�
  *
  */

/**
 * @brief table_t ��ʾһ�� table ��������
 *
 * ͨ�� table_* ϵ��API����table���д��������١����ʵȲ�����
 */
typedef void * table_t;

 /**
  * @brief table Ŀǰ֧�ֵ��ֶ���������
  */
enum table_filed_type {
	/**
	 * @brief �գ������壬ռλ��
	 */
	tft_null,
	/**
	 * @brief 1 �ֽ�����������Ϊ c
	 */
	tft_char,
	/**
	 * @brief 2 �ֽ�����������Ϊ h
	 */
	tft_short,
	/**
	 * @brief 4 �ֽ�����������Ϊ i    
	 */
	tft_int,
	/**
	 * @brief 8 �ֽ�����������Ϊ q
	 */
	tft_int64,
	/**
	 * @brief 4 �ֽڸ��㣬����Ϊ f
	 */
	tft_float,
	/**
	 * @brief 8 �ֽڸ��㣬����Ϊ d
	 */
	tft_double,
	/**
	 * @brief 8 �ֽ�ָ���ַ�����ָ�룬����Ϊ s 
	 */
	tft_str,
	/**
	 * @brief 8 �ֽ�ָ��table_t��ָ�룬����Ϊ t 
	 */
	tft_table,
	/**
	 * @brief 1 �ֽ�����������Ϊ C
	 */
	tft_uchar,
	/**
	 * @brief 2 �ֽ�����������Ϊ H
	 */
	tft_ushort,
	/**
	 * @brief 4 �ֽ�����������Ϊ I    
	 */
	tft_uint,
	/**
	 * @brief 8 �ֽ�����������Ϊ Q
	 */
	tft_uint64,
	/**
	 * @brief 8 �ֽ�ָ��䳤�����Ƶ�ָ�룬����Ϊ b
	 */
	tft_binpt,
	/**
	 * @brief 8 �ֽ�ʱ��������������Ϊ T
	 */
	tft_timet,
	/**
	 * @brief 8 �ֽڶ��㸡����������Ϊ p
	 */
	tft_pfloat,
	/**
	 * @brief 8 �ֽڶ��㸡����������Ϊ v
	 */
	tft_vfloat
};

enum key_col_order {
	ASC,
	DESC
};
typedef enum key_col_order KEYORDER;

/**
 * @name ������ɾ�������л����
 * @{ */

/**
 * @brief table_create ���ڴ���һ�� table
 *
 * @param schema table�ĸ�ʽ�����ַ������ο� \ref sec_schema
 * @param rows ������������ͨ�� \ref table_rows ��������
 * @param name table������ \ref table_name
 *
 * @return ���ش����ɹ��� table��ͨ�� \ref table_destory ���٣���Ϊ NULL ���ʾ����ʧ��
 */
TABLE_API table_t table_create(const char * schema, size_t rows, const char * name);
/**
 * @brief table_clone �Ը����� table ����һ�����(Deep Copy)
 *
 * һ����˵��table ����ͨ�� table_assign ���������ü�����ʹ����԰�ȫ�Ĵ��ݵ�������ģ���С�
 * ������ table �������̰߳�ȫ�ģ�ͨ�������̼߳乲�� table ʱ��Ӧ�ö� table ����һ�� clone��
 *
 * clone ��� table ��Դtable������ȫһ�µĽṹ���������ü�������Ϊ 1
 *
 * @param table ������ table
 *
 * @return �����ɵ� table
 */
TABLE_API table_t table_clone(table_t table);
/**
 * @brief table_assign Ϊ������table�������ü���
 *
 * �������µĳ�������ͬһ�߳���
 * \code
 *
 *
 * void func(){
 *    table_t t = table_create(...);
 *    SendMessage(hWnd, WM_DATACOMING 0, table_assign(t));
 *    SendMessage(hWnd, WM_DATACOMING 0, table_clone(t));
 *    table_destory(t);
 * }
 *
 * void OnDataComing(table_t t){
 *    // ...
 *    table_destory(t);
 * }
 * \endcode
 *
 * ��ʱ��ʹ�� table_assign ���� table_clone ������Ч��
 *
 * @param table ������table
 *
 *
 * @return �����������ü������ table
 */
TABLE_API table_t table_assign(table_t table);
/**
 * @brief table_destory ��������һ�� table
 *
 *
 * @param table �ɷ��� table_t ����ӦAPI�ķ���ֵ
 *
 * @sa table_create table_clone table_assign table_frombuff
 */
TABLE_API void table_destory(table_t table);
/**
 * @brief table_tobuff ��һ�������� table ���л���һ�黺����
 *
 * ������ buff ָ�������СӦ������Ϊ \ref table_size, ���л���ǡ��
 * ʹ�� table_size ��С�Ļ���
 *
 * @param table ������ table
 * @param buff �����Ļ���
 * ���л�����ڴ�ṹ��
 * schema string
 * name string
 * rows int32
 * col1 rows * cell
 * col2 rows * cell
 * ...
 * colN rows * cell
 * attribute
 * nullflag rows * cols * 1byte

 * cell = char|short|int32|...|double|string|binary|table
 * string = length*1byte '\0'
 * binary = length length*1byte
 * table = length table_size()*1byte
 *
 * attribute ����˳��Ϊ table_attrib col1_atrrib ... colN_attrib.
 * һ�����Խṹ�ǣ�str_num(int32),str_key1+'\0',str_val1+'\0'....int_num(int32),int_key1,int_val1....
 */
TABLE_API void table_tobuff(table_t table, char * buff);
/**
 * @brief table_frombuff ��һ�黺���з����л���һ�� table
 *
 * @param buff ������ buff��ͨ�������buff�������� table_tobuff �����
 * @param len buff �Ĵ�С
 *
 * @return �����л����� table
 */
TABLE_API table_t table_frombuff(const char * buff, size_t len);
/**
 * @brief table_tobuff_extra ��һ�������� table ���л���һ�黺����
 *
 * ������ buff ָ�������СӦ������Ϊ \ref table_size_extra, ���л���ǡ��
 * ʹ�� table_size_extra ��С�Ļ���
 *
 * @param table ������ table
 * @param buff �����Ļ���
 * @param extra �����ļ��ܴ�
 * ���л�����ڴ�ṹ
 * version int32
 * schema string
 * name string
 * extra string
 * rows int32
 * col1 rows * cell
 * col2 rows * cell
 * ...
 * colN rows * cell
 * nullflag rows * cols * 1byte

 * cell = char|short|int32|...|double|string|binary|table
 * string = length*1byte '\0'
 * binary = length length*1byte
 * table = length table_size_extra()*1byte 
 */
TABLE_API void table_tobuff_extra(table_t table, char * buff, const char * extra = NULL);
/**
 * @brief table_frombuff_extra ��һ�黺���з����л���һ�� table
 *
 * @param buff ������ buff��ͨ�������buff�������� table_tobuff �����
 * @param len buff �Ĵ�С
 *
 * @return �����л����� table
 */
TABLE_API table_t table_frombuff_extra(const char * buff, size_t len);

/**
 * @brief table_row_tobuff ��һ�������� table��һ�����л���һ�黺����
 *
 * ������ buff ָ�������СӦ������Ϊ \ref table_row_size, ���л���ǡ��
 * ʹ�� table_row_size ��С�Ļ���
 *
 * @param table ������ table
 * @param buff �����Ļ���
 *
 */
TABLE_API void table_row_tobuff(table_t table, size_t row, char * buff);
/**
 * @brief table_row_frombuff ��һ�黺���з����л���һ�� table
 *
 * @param buff ������ buff��ͨ�������buff�������� table_row_tobuff �����
 * @param len buff �Ĵ�С
 *
 * @return �����л����� table
 */
TABLE_API void table_row_frombuff(table_t table, size_t row, const char * buff, size_t len);
/**
 * @brief table_move_colsname ���ո������������滻��������
 *
 * �ο� \ref table_sort
 *
 * @param table ������ table
 * @param srcColsName ������
 * @param dstColsName ��������
 *
 * @return ƥ�䵽���к��б�
 */
TABLE_API table_t table_move_colsname(table_t table, const char * srcColsName, const char * dstColsName);
/**
 * @brief table_clean_schema_pool ���schema�����
 *
 */
TABLE_API void table_clean_schema_pool(void);

/**  @} */

/**
 * @name ���Ӻ�����
 * @{ */

/**
 * @brief table_append �ڸ����� table ������һ��
 *
 * �� table �����ӽ�ʹ table �ڲ����ڴ治������������һЩ�� table ��Ӧ�� C �ṹ�Ĳ�����
 * ʧЧ�����Ե��� table_tidy ����������ʹ���ڴ���������Ƶ�������������������⡣
 *
 * @param table ������ table
 *
 * @return ���Ӻ�õ����к�
 */
TABLE_API size_t table_append(table_t table);


/**
 * @brief table_tidy �����ڲ����ڴ棬ʹ���Ϊ������һ��
 *
 * table �ڴ���֮�����ڲ����ڴ��������ģ����Կ���ͨ�� table_get_buff(t, 0, 0) ������
 * ����һ��C�ṹʹ�ã������� table_append ֮����������������ϣ�����Ҫ�������ƵĲ�����
 * ����ͨ������ table_tidy ����������
 *
 * @param table ������ table
 *
 */
TABLE_API void table_tidy(table_t table);


/**
 * @brief table_is_tidy ��ѯ�ڲ����ڴ��Ƿ�Ϊ������һ��
 *
 *
 * @param table ������ table
 *
 * @return �Ƿ�����
 */
TABLE_API bool table_is_tidy(table_t table);


/**  @} */

/**
 * @name ����
 * @{ */

/**
 * @brief table_rows ���� table ������
 *
 * @param table ������table
 *
 * @return ����
 */
TABLE_API size_t table_rows(table_t table);
/**
 * @brief table_cols ���� table ������
 *
 * @param table ������ table
 *
 * @return ����
 */
TABLE_API size_t table_cols(table_t table);
/**
 * @brief table_size ����table���л���Ĵ�С
 *
 * @param table ������table
 *
 * @return ���л���Ĵ�С����
 */
TABLE_API size_t table_size(table_t table);
/**
 * @brief table_size_extra ����table���л���Ĵ�С
 *
 * @param table ������table
 *
 * @return ���л���Ĵ�С���������л���������Ϣ,Ϊ������������
 */
TABLE_API size_t table_size_extra(table_t table);
/**
 * @brief table_pod_size ���� table POD ���ֵĴ�С
 *
 * POD��ָ��Щ����ʱ��Ԥ֪�����ͣ������������������ַ�����table������POD
 * ���һ�� table ֻ�� POD ���ͣ���ô���������л��� clone ������Ч�ʣ�ͬʱ
 * ��Ҳ����ͨ������һ��C�ṹ�������п��ٵķ��ʡ�
 *
 * ����ͬ sizeof(T) * rows
 *
 * @param table ������table
 *
 * @return POD���ֵĴ�С
 */
TABLE_API size_t table_pod_size(table_t table);
/**
 * @brief table_width ���� table �Ŀ�
 *
 * ����ͬ sizeof(T)
 *
 * @param table ������table
 *
 * @return sizeof �Ľ��
 */
TABLE_API size_t table_width(table_t table);
/**
 * @brief table_schema ���� table �Ķ����ַ���
 *
 * @param table ������table
 *
 * @return �����ַ���
 */
TABLE_API const char * table_schema(table_t table);
/**
 * @brief table_name ���� table ������
 *
 * �ڴ���tableʱ�����Զ������� \ref table_create
 *
 * @param table ����������
 *
 * @return table ������
 */
TABLE_API const char * table_name(table_t table);
/**
 * @brief table_is_pod ���Ը�����table�Ƿ�Ϊ POD ����
 *
 * �������ַ���(s)��table(t)�ֶε�table��Ϊ POD����
 *
 * @param table ������ table
 *
 * @return true ��ʾΪPOD����
 */
TABLE_API bool table_is_pod(table_t table);

/**
 * @brief table_col_index �������Ʒ����е����
 *
 * ��Ӧ����һ��ѭ���з����ĵ��ô˺�������Ӧ����ѭ���⻺��˺����ķ���ֵ��
 * Ȼ����������Ĳ���
 *
 * @param table ������table
 * @param name ������
 *
 * @return -1 ��ʾ���в�����
 */
TABLE_API size_t table_col_index(table_t table, const char * name);
/**
 * @brief table_col_offset ����ĳһ�о࿪ʼ��ƫ��
 *
 * �Խṹ Day Ϊ����open �ֶε�ƫ��Ϊ 8��low �ֶε�ƫ��Ϊ 16
 *
 * @param table ������table
 * @param col ��ID
 *
 * @return 
 */
TABLE_API size_t table_col_offset(table_t table, size_t col);
/**
 * @brief table_col_type ����ĳһ�е�����
 *
 * @param table ������table
 * @param col ��ID
 *
 * @return �ο� \ref table_filed_type
 */
TABLE_API int table_col_type(table_t table, size_t col) ;
/**
 * @brief table_col_size ����ĳһ�еĴ�С
 *
 * �Խṹ Day Ϊ����date �ֶεĴ�СΪ 8��low �ֶεĴ�СΪ 4
 *
 * @param table ������ table
 * @param col ��ID
 *
 * @return �д�С
 */
TABLE_API size_t table_col_size(table_t table, size_t col);
/**
 * @brief table_col_name ���ظ����е�����
 *
 * @param table ������ table
 * @param col ��ID
 *
 * @return ������  �ο� \ref table_col_index
 */
TABLE_API const char * table_col_name(table_t table, size_t col);
/**
 * @brief table_pkcol ����������
 *
 * @param table ������ table
 * 
 * @return ������ID,
 */
TABLE_API const size_t table_pkcol(table_t table);
/**
 * @brief table_pkorder ������������ʽ
 *
 * @param table ������ table
 * 
 * @return ��������ʽ
 */
TABLE_API KEYORDER table_pkorder(table_t table);
/**
 * @brief table_row_size ����һ�еĴ�С
 * 
 * @param table ������ table
 * @param row �к�
 *
 * @return �д�С
 */
TABLE_API size_t table_row_size(table_t table, size_t row);
/**
 * @brief table_col_isnull �����ֶ�ֵ�Ƿ�ΪNULL
 * 
 * @param table ������ table
 * @param row �к�
 * @param col ��ID
 *
 * @return true or false
 */
TABLE_API bool table_col_isnull(table_t table, size_t row, size_t col);

/**  @} */

/**
 * @name ȡֵ���
 * @{ */

TABLE_API int table_get_int(table_t table, size_t row, size_t col);
TABLE_API long long table_get_int64(table_t table, size_t row, size_t col);
TABLE_API unsigned int table_get_uint(table_t table, size_t row, size_t col);
TABLE_API unsigned long long table_get_uint64(table_t table, size_t row, size_t col);
TABLE_API float table_get_float(table_t table, size_t row, size_t col);
TABLE_API double table_get_double(table_t table, size_t row, size_t col);
TABLE_API const char * table_get_str(table_t table, size_t row, size_t col);
TABLE_API const table_t table_get_table(table_t table, size_t row, size_t col);
TABLE_API const char * table_get_binary(table_t table, size_t row, size_t col);
TABLE_API const size_t table_get_binary_len(table_t table, size_t row, size_t col);
TABLE_API const size_t table_get_time_t(table_t table, size_t row, size_t col);
TABLE_API const long long table_get_time(table_t table, size_t row, size_t col);
TABLE_API const long long table_get_pfloat(table_t table, size_t row, size_t col);
TABLE_API const long long table_get_vfloat(table_t table, size_t row, size_t col);
TABLE_API short int table_get_short(table_t table, size_t row, size_t col);
/**
 * @brief table_get_buff ����ĳһ�е�ָ��
 *
 * ���еĸ�ʽ��Ϊ1ʱ����ͨ����ʾ����Ϊһ����֪��С���Զ�������ݣ���һ��̶���С�Ļ���ȡ�
 * ��ʱ���ԣ�ͨ������������ȡ����table���ڴ��ָ�룬ָ��ָ����ڴ�İ�ȫ��С�� table_col_size ��
 *
 * ��ʱ����Ҫ�� table ת��ΪC�ṹ֮����ʣ�Ҳ���Ե��ô˺���
 * \code
 * const Day * day = (const Day *)table_get_buff(t, 0, 0);
 * for(int row = 0; row < table_rows(t); row++){
 *     printf("%lld\n", day[row].date);
 * }
 * \endcode
 *
 * @param table ������ table
 * @param row ��
 * @param col ��
 *
 * @return ���ݵ��ڴ�ָ��
 */
TABLE_API const void * table_get_buff(table_t table, size_t row, size_t col);

/**  @} */

/**
 * @name �������
 * @{ */

TABLE_API void table_set_int(table_t table, size_t row, size_t col, int val);
TABLE_API void table_set_int64(table_t table, size_t row, size_t col, long long val);
TABLE_API void table_set_uint(table_t table, size_t row, size_t col, unsigned int val);
TABLE_API void table_set_uint64(table_t table, size_t row, size_t col, unsigned long long val);
TABLE_API void table_set_float(table_t table, size_t row, size_t col, float val);
TABLE_API void table_set_double(table_t table, size_t row, size_t col, double val);
TABLE_API void table_set_pfloat(table_t table, size_t row, size_t col, long long val);
TABLE_API void table_set_vfloat(table_t table, size_t row, size_t col, long long val);
TABLE_API void table_set_short(table_t table, size_t row, size_t col, short int val);

/**
 * @brief table_set_str_raw �����ַ������������ڴ������ table
 *
 * val ������һ��ʹ�� table_strnew ���� table_strdup �������ַ�����
 * ����Ҳ��Ӧ����ͨ�� table_strdel �ͷţ�ʹ�ô˽ӿڣ�
 * ��ĳЩ����¿��Լ���һ���ַ������ơ�table �ڲ�ԭ�ȵ��ַ������ᱻ�ͷš�
 *
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 * @param val �ַ���
 *
 * @return 
 */
TABLE_API void table_set_str_raw(table_t table, size_t row, size_t col, char * val);
TABLE_API void table_set_table_raw(table_t table, size_t row, size_t col, table_t val);
//TABLE_API void table_set_binary_raw(table_t table, size_t row, size_t col, size_t len,const char * val);
/**
 * @brief table_set_str �����ַ���
 *
 * �������ַ����������ڲ�ͨ�� table_strdup ����һ�ݿ�����Ȼ��ͨ��
 * table_set_str_raw ��������
 *
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 * @param val �ַ���
 * @param delold �Ƿ�ɾ������λ��ԭ�е��ַ�����һ����˵��Ӧ�ô� ture
 *
 */
TABLE_API void table_set_str(table_t table, size_t row, size_t col, const char * val, bool delold);
TABLE_API void table_set_table(table_t table, size_t row, size_t col, const table_t val, bool delod);
TABLE_API void table_set_binary(table_t table, size_t row, size_t col, size_t len,const char * val, bool delod);
/**
 * @brief table_set_buff Ϊһ������Ϊ buffer ������������
 *
 * ���� (const char*)buff + offset ���� len �ֽڵ� table �ڲ�
 *
 * @param table
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 * @param buff Դ����
 * @param len ��Ҫ���Ƶĳ���
 * @param offset ����Դ�� offest ��ʼ����
 *
 * @return 
 */
TABLE_API void table_set_buff(table_t table, size_t row, size_t col, const void * buff, size_t len,size_t offset);

/**
 * @brief table_set_time Ϊһ������Ϊ time ������������
 *
 * @param table
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 * @param sec time_t ʱ��
 * @param msec ������
 *
 * @return 
 */
TABLE_API void table_set_time(table_t table, size_t row, size_t col, size_t sec, int msec);

/**
 * @brief table_col_writenull д��NULLֵ
 *
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 *
 */
TABLE_API void table_col_writenull(table_t table, size_t row, size_t col);

/**  @} */

/**
 * @name ��ȡǿ��ת���������
 * @{ */

/**
 * @brief table_cast_double ��ȡ double ����
 *
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 *
 */
TABLE_API double table_cast_double(table_t table, size_t row, size_t col);

/**
 * @brief table_cast_int64 ��ȡ int 64 ����
 *
 * @param table ������ table
 * @param row �к�
 * @param col �к�
 *
 */
TABLE_API long long table_cast_int64(table_t table, size_t row, size_t col);

/**  @} */


/**
 * @name �߼�����
 * @{ */
/**
 * @brief table_fill ��һ�� table ��ָ���и��Ƶ���һ�� table ��ָ������
 *
 * �ڸ���ʱ��ֻ������ƥ����ֶλ���и��ƣ������ַ�����table���͵��ֶΣ�
 * Ҳ�������Ӧ�� clone��
 *
 * ���磬�� table ��һ�������б��ȫ����������ֻ��ĳЩ��Ʒ��ĳЩ�������͵�ʱ��
 * ����ͨ���˷���������ȫ����
 *
 * @param table Ŀ��table
 * @param drow  Ŀ����
 * @param other Դtable
 * @param srow  Դ��
 *
 */
TABLE_API void table_fill(table_t table, size_t drow, const table_t other, size_t srow);
/**
 * @brief table_update ��һ��Դ table ���µ�һ��Ŀ��table��
 *
 * Դtable��Ŀ��tableӦ�����پ���һ����ͬ���Ƶ��У�����н�����Ϊkey���ڸ���ʱ��
 * ��ƥ��key��Դ�к�Ŀ������ table_fill
 *
 * @param table Ŀ��table
 * @param other Դtable
 * @param keycol ������
 *
 */
TABLE_API void table_update(table_t table, const table_t other, const char * keycol);
/**
 * @brief table_select ��һ��table�л�ȡһ���Ӽ�
 *
 * �²�����table����Ϊ fields ����ĸtableƥ�䵽���У�����Ϊ min(count, ĸ���� - from)
 *
 * @param table ĸtable
 * @param fields �ֶε��б�ʹ��,�ָ���ַ���
 * @param from ĸtable����ʼ�к�
 * @param count ��ิ�Ƶĸ���
 *
 * @return �Ӽ���˳�򽫿��ܵİ��� fields ���˳�򣬵����������ֶβ����ڻ��ظ���
 * ��ᱻ����
 */
TABLE_API table_t table_select(table_t table, const char * fields, size_t from, size_t count);
/**
 * @brief table_join ���ո����н����� table ���кϲ�
 *
 * �ϲ����table����Ϊ����Դtable�еĲ���ȥ���ظ�����
 * \code
 * table_join("f1;f2;f3", "f1;f3;f4") = "f1;f2;f3;f4"
 * \endcode
 * ����Ϊ Դ1����, �� left join ������һ��
 *
 * @param table Դ1
 * @param other Դ2
 * @param keycol ������
 *
 * @return 
 */
TABLE_API table_t table_join(table_t table, table_t other, const char * keycol);

enum{
	TABLE_STR_COMPARER = 0,
	TABLE_INT_COMPARER,
	TABLE_INT64_COMPARER,
	TABLE_FLOAT_COMPARER,
	TABLE_DOUBLE_COMPARER,
	TABLE_MAX_COMPARER
};

typedef int (*field_compare_func)(void * table, size_t r1, size_t r2, void * userdata);
typedef int (*value_compare_func)(void * table, size_t row, size_t col, void * userdata);
typedef TABLE_API char * (*table_malloc_func)(size_t bytes);
typedef TABLE_API void (*table_free_func)(char * ptr);

/**
 * @brief table_sort ���ո����ĺ�����table��������
 *
 * table_sort ���Ƿ���һ��һ�е� table���䶨��Ϊ "sn:i"��������������table
 * ��ͬ��ÿһ���е�����Ϊ�������кš�
 * ����
 * \code
 * table_t table = table_create("f1:i;f2:i", 3, "");
 * table_set_int(table, 0, 0, 2);
 * table_set_int(table, 0, 0, 1);
 * table_set_int(table, 0, 0, 3);
 *
 * // �Ե�һ�а������������������
 * table_t sorted = table_sort(table, INT_FIELD_COMPARER, 0);
 *
 * for(size_t i = 0; i < table_rows(sorted); i++)
 *     printf("%d ", table_get_int(sorted, i, 0));
 * table_destory(sorted);
 * table_destory(table);
 *
 * // �����
 * // 1 0 2
 * \endcode
 *
 * Ԥ������������������ڼ򵥹��������
 *
 * @param table ������ table
 * @param comparer �ȽϺ���
 * @param userdata �ڱȽ�ʱ���ݵĲ���
 *
 * @return �������к��б�
 */
TABLE_API table_t table_sort(table_t table, field_compare_func comparer, void * userdata);

/**
 * @brief table_filter ���ո�����ƥ�亯����ѡ������������
 *
 * �ο� \ref table_sort
 *
 * @param table ������ table
 * @param comparer ƥ�亯��
 * @param userdata ƥ����Զ������
 *
 * @return ƥ�䵽���к��б�
 */
TABLE_API table_t table_filter(table_t table, field_compare_func comparer, void * userdata);

/**
 * @brief table_group ��������table����ĳһ��������
 
 * table_group �������һ��������table���䶨��Ϊ
 * \code
 * // ��Դ table ����Ϊ
 * const char * table_schema = "f1:s;f2:d;f3:i"
 * // ���� f1 �� group �������table�Ķ���Ϊ
 * const char * group_schema = "f1:s;f2:5d;f2:5d;_ROWS_:t";
 * // ���У�_ROWS_ �Ķ���Ϊ
 * const char * group_rows_schema = "sn:i";
 * // ��ʾ��ǰ������кŵ��б�
 *
 * // ÿһ����ֵ���͵��ֶΣ�����л�����ͳ�ƣ����� (count, sum, avg, max, min) ��Ԫ��
 *
 * table_t table = table_create(table_schema, 5, "");
 * // �����µı������ table ������
 * // a 1 4
 * // a 2 3
 * // b 3 2
 * // b 4 1
 * // c 1 1
 * table_t grouped = table_group(table, "f1");
 * // �� grouped ������Ϊ
 * // f1        f2              f3           _ROWS_
 * // a (2, 3, 1.5, 2, 1) (2, 7, 3.5, 4, 3) [0, 1]
 * // b (2, 7, 3.5, 4, 3) (2, 1, 1.5, 2, 1) [2, 3]
 * // c (1, 1, 1  , 1, 1) (1, 1, 1  , 1, 1) [5]
 * 
 * \endcode
 * �����ַ��� table ���͵��У�ͳ��ֵ����Ϊ 0
 *
 * @param table
 * @param keycol
 *
 * @return 
 */
TABLE_API table_t table_group(table_t table, const char * keycol);

/**
 * @brief table_delete ɾ��table�дӵ�row�п�ʼ��num�У�������row�У�
 *
 * @param table ������ table
 * @param row   ��ɾ������ʼ��
 * @param num   ɾ����������
 *
 * @return ƥ�䵽���к��б�
 */
TABLE_API void table_delete(table_t table, size_t row, size_t num);

/**
 * @brief table_insert �ڵ�row��֮ǰ����num��
 *
 * @param table ������ table
 * @param row   ����λ�ã�ԭtable����֮ǰ
 * @param num   �����������
 *
 * @return ƥ�䵽���к��б�
 */
TABLE_API void table_insert(table_t table, size_t row, size_t num);


/**  @} */



/**
 * @name �ַ������ڴ�
 * @{ */
TABLE_API void table_set_alloctor(table_malloc_func malloc_func, table_free_func free_func);
TABLE_API char * table_strnew(size_t bytes);
TABLE_API void table_strdel(char * s);
TABLE_API char * table_strdup(const char * s);

/**  @} */

/**
 * @name ���úͶ�ȡ�Զ�������
 * @{ */
TABLE_API bool table_getkv_string(table_t table, const char* key, char* val, size_t val_size);
TABLE_API bool table_setkv_string(table_t table, const char* key, const char* val);
TABLE_API bool table_col_getkv_string(table_t table, size_t col, const char* key, char* val, size_t val_size);
TABLE_API bool table_col_setkv_string(table_t table, size_t col, const char* key, const char* val);
TABLE_API bool table_setkv_value(table_t table, int key, int val);
TABLE_API bool table_getkv_value(table_t table, int key, int * val);
TABLE_API bool table_col_setkv_value(table_t table, size_t col, int key, int val);
TABLE_API bool table_col_getkv_value(table_t table, size_t col, int key, int * val);
TABLE_API const size_t table_kv_string_len(table_t table, const char* key);
TABLE_API const size_t table_col_kv_string_len(table_t table, size_t col, const char* key);
/**  @} */

#ifdef TABLE_WITH_SQLITE3

#include <sqlite.h>

TABLE_API table_t table_from_sqlite3(sqlite3 * sqlite, const char * sql);
TABLE_API table_t table_from_sqlite3_stmt(sqlite3 * sqlite, sqlite3_stmt * stmt);

#endif // TABLE_WITH_SQLITE3

#ifdef TABLE_WITH_MYSQL

TABLE_API table_t table_from_mysql(MYSQL * mysql, MYSQL_RES * result);

#endif // TABLE_WITH_MYSQL

#ifdef __cplusplus
}	// extern "C"
#endif

#endif
