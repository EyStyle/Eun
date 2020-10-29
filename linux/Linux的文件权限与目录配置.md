# Linux的文件与目录管理

1、用户、用户组、其他人

文件权限与属性：

            chgrp: 改变文件所属用户组    # chgrp [-R]  用户组名称  dirfilename/filename
            chown: 改变文件所有者            # chown [-R] 账号名称 dirfilename/filename
            chown: 改变文件所有者            # chown [-R] 账号名称:组名 dirfilename/filename
            chmod: 改变文件的权限            # chmod [-R] xyz 文件或目录 (xyz: 数字属性—>4、2、1)
                    chmod [-R] u=rwx,go=rx 文件或目录
                    chmod [-R] u+w,o-x 文件或目录
             
             uname -r        # 查看实际的内核版本
             lsb_release -a    # 查看内核和distribution信息

2、文件与目录管理

        pwd [-P]: 显示当前目录, -P: 显示当前的路径，而非使用连接(link)路径
        mkdir: 新建目录
            -m:    配置文件案的权限，直接设置，不需要看默认权限
            -p:    将所需目录(包括上层目录)递归创建起来
        rmdir: 删除一个空的目录，仅能“删除空的目录”
            -p:    连同上层“空的”目录也一起删除

        cp:    复制        # cp [-adfilprsu] source    destination
        rm:    移除文件或目录        # rm [-fir] 文件或目录
            -f:    force，忽略不存在的文件
            -i:    互动模式，在删除前询问是否操作
            -r:    递归删除
        mv:    移动文件与目录，或更名        # mv    [-fiu]    source destination
            -f:    force，忽略不存在的文件
            -i:    互动模式，询问是否操作
            -u:    若目标文件已存在，且source比较新，才会更新

        basename /etc/sysconfig/network    ==>    network    取得文件名
        dirname /etc/sysconfig/network    ==>    /etc/sysconfig    取得目录名

        touch:    修改文件时间或新建文件    # touch    [-acdmt]    文件
            -a:    仅修改访问时间
            -c:    仅修改文件时间
            -d:    后面可以接欲修改的日期而不用目前的日期，也可以使用 --date="日期或时间"
            -m:    仅修改 mtime
            -t:    后面可以接欲修改的时间而不用目前的时间，格式[YYMMDDhhmm]

3、文件内容查阅

       cat:    由第一行开始显示文件内容
           -n:    显示行号
           -b:    仅对非空白行列出行号
           -v:    打印一些看不出来的特殊字符
       tac:    从最后一行开始显示文件内容
       nl:    显示的时候，顺便输出行号        # nl [-bnw] 文件
           -b:    
                   -b    a:    表示不论是否为空行，都列出行号
                   -b    t:    仅对非空白行列出行号
           -n:
                   -n    ln:    行号在屏幕左方显示，仅对非空白行列出行号
                   -n    rn:    行号在屏幕右方显示，且不加 0, ，对非空白行列出行号
                   -n    rz:    行号在自己字段的最右方显示，且加 0
           -w:    行号字段占用的位置
           
       more:    一页一页的显示文件内容
           space:    向下翻一页
           Enter:    向下滚动一行
           /字符串:    向下查询该关键字
           :f:    立刻显示文件名以及目前显示的行数
           q:    立刻离开more
           b或[Ctrl]-b:    往回翻页，仅对文件有用
       less:    与more类似，可以往前翻页
           space:    向下翻动一页
           [PageDown]:    向下翻动一页
           [PageUp]:    向上翻动一页
           /字符串:    向下查询该关键字
           ?字符串:    向上查询字符串
           
       head:    只看头几行
       tail:    只看结尾几行
       od:    以二进制的方式读取文件内容    # od [-t    TYPE]    文件
           -t:    TYPE
                   a:    默认字符数出
                   c:    使用ASCII码输出
                   d:    使用十进制输出
                   f:    使用浮点数输出
                   o:    使用八进制输出
                   x:    使用十六进制输出
           