# Mini-network-diagnostician ——基于QT开发的一个网络诊断小工具
      
### 工作逻辑： 
          1.手动选择文件打开
          2.新线程拿到打开文件的内容进行解析处理；
          3.利用信号槽（SIGNAL/SLOT）进行解析结果的返回；
          4.在弹窗界面显示解析结果；
          5.工作线程的成员函数Run()，进行while(1)进行循环实时检测。
          
          
## 待优化：
      1.可以在弹窗之前增加一个解析的界面设计   
      2.每一个大段前打印一次Log      
      3.窗口伴随下移
