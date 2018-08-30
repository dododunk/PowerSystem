
	业务交易的代码都将尽量实现模板式的开发。
	为此

	为工程开发和目录简洁。各交易工程的目录经过重新组织编排

其中：
1.需要手动修改Dialogxxx（Dialogxxx.h,Dialogxxx.cpp）代码的，放在和工程dspw文件同一目录。

2.资源文件（用VC IDE进行编辑）和其他基本属于模板性质的文件，放在template目录下。


3.各工程库都要调用到的一些公用函数放在../../utils目录下


4.工程生成的dll在目录	../../bin/debug
						../../bin/release
    中间生成文件在目录	../../bin/tmp/project_xxx/debug
						../../bin/tmp/project_xxx/release	