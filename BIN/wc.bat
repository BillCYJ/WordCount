@echo off
.\wc.exe -c -w -l input.txt -o result.txt//正确形式
.\wc.exe -c -w -l test_null.txt -o result.txt//空文件
.\wc.exe -c -w -l test_space.txt -o result.txt//只有换行符和空格的情况
.\wc.exe//只有.exe的情况
.\wc.exe -z -w -l input.txt//参数错误
.\wc.exe -c -c -l input.txt -o result.txt//参数重复
.\wc.exe -c -w -l input.txt -o//没有输出文件名
.\wc.exe -c -w -o input.txt -l result.txt//-o在错误的位置
.\wc.exe -c -w -l temp.txt -o result.txt//输入文件不存在
.\wc.exe -c -w -l -o result.txt//未指定输入文件


