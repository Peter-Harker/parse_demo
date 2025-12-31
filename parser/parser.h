#ifndef PARSER_H  // 头文件保护开始：如果未定义 PARSER_H
#define PARSER_H  // 定义 PARSER_H，防止后续重复包含

// 引入依赖的标准库
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 定义解析状态枚举：标识解析的各种结果
typedef enum {
    PARSE_SUCCESS,    // 解析成功
    PARSE_EMPTY,      // 待解析字符串为空
    PARSE_INVALID,    // 解析内容格式无效（无=、键/值为空等）
    PARSE_MEM_ERROR   // 内存分配失败
} ParseStatus;

// 2. 定义解析结果数据结构：存储 "key=value" 解析后的键值对
typedef struct {
    char *key;        // 解析后的键（动态分配内存，需手动释放）
    char *value;      // 解析后的值（动态分配内存，需手动释放）
} KeyValuePair;

// 3. 核心解析函数声明：对外暴露的接口，主程序将调用该函数
// 功能：解析 "key=value" 格式字符串，填充 KeyValuePair 结构体，返回解析状态
ParseStatus parse_key_value(const char *input_str, KeyValuePair *result);

// 4. 辅助函数声明：释放 KeyValuePair 中的动态内存，防止内存泄漏
void free_key_value(KeyValuePair *kv_pair);
// 新增：代码行统计函数声明
// 功能：统计指定文件的有效代码行数（排除纯空行）
// 参数：file_path - 目标文件路径（如 "main.c"）；line_count - 输出参数，存储统计结果
// 返回值：ParseStatus - 统计状态（成功/文件不存在/参数无效等）
ParseStatus count_file_lines(const char *file_path, int *line_count);

#endif // PARSER_H  // 头文件保护结束

