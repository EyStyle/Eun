## 变量键盘读取、数组与声明：read, array, declare
  
  read [-pt] variable
    -p: 后面可以接输入提示符
    -t: 后面接等待的秒数，过了时间则失效
    
  declare [-aixr] variable
    -a: 声明一个数组 array
    -i: 声明一个整型 integer
    -x: 声明一个环境变量
    -r: 将变量设置为 (readonly) 类型，不可更改内容，也不可重设
    
