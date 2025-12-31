#include "parser/parser.h"

int main() {
    // ========== 原有：键值对解析功能（不变） ==========
    KeyValuePair result;
    result.key = NULL;
    result.value = NULL;
    const char *test_input = "username=zhengjiayang";
    ParseStatus parse_status = parse_key_value(test_input, &result);

    // 输出解析结果
    printf("===== 键值对解析功能 =====\n");
    switch (parse_status) {
        case PARSE_SUCCESS:
            printf("解析成功！\n键（key）：%s\n值（value）：%s\n", result.key, result.value);
            break;
        case PARSE_EMPTY:
            printf("解析失败：待解析字符串为空！\n");
            break;
        case PARSE_INVALID:
            printf("解析失败：字符串格式无效（需满足 key=value 格式）！\n");
            break;
        case PARSE_MEM_ERROR:
            printf("解析失败：内存分配失败！\n");
            break;
        default:
            printf("解析失败：未知错误！\n");
            break;
    }
    // 释放动态内存，避免泄漏
    free_key_value(&result);

    // ========== 新增：代码行统计功能（核心新增） ==========
    printf("\n===== 代码行统计功能 =====\n");
    int valid_line_num; // 存储有效行数
    // 统计 main.c 文件的有效行数（可替换为 "parser/parser.c" 测试其他文件）
    ParseStatus count_status = count_file_lines("main.c", &valid_line_num);

    // 输出统计结果
    if (count_status == PARSE_SUCCESS) {
        printf("行统计成功！%s 有效代码行数：%d\n", "main.c", valid_line_num);
    } else {
        printf("行统计失败！原因：文件不存在或参数无效\n");
    }

    return 0;
}
