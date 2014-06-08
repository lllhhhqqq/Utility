/** 
 * @file disallow_copy_assign.h
 * @brief 
 * @author Luhaoqing 
 * @date 2013/11/22
 */
#ifndef DISALLOW_COPY_ASSIGN_H
#define DISALLOW_COPY_ASSIGN_H

#define DISALLOW_COPY_ASSIGN(Type) \
Type(Type const&); \
Type& operator=(Type const&);

#endif