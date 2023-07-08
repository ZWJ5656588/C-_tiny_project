#include"order_file.h"

// 这个cpp文件用来显示学生的预约状态

// 截取字符串的封装函数、
void Sub_info(string s,string &key,string &value, map<string, string>&m)
{
    int pos = s.find(":"); // 4
        if (pos != -1)
        {
            key = s.substr(0,pos); // 从0号位置开始 截4个字符
            value = s.substr(pos + 1,s.length()-pos-1); // 截取：后的位置到最后

            m.insert(make_pair(key,value));
        }
}



//构造函数

OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE,ios::in);

    string date;    // 日期
    string interval; // 时间段
    string stuId;  // 学生编号
    string stuName; //学生姓名
    string roomId;  //机房编号
    string status; //预约状态

    this->m_Size = 0; // 记录条数

    while(ifs >> date && ifs >>interval && ifs >> stuId &&
     ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        // cout << date << endl;
        // cout << interval  << endl;
        // cout << stuId << endl;
        // cout << stuName << endl;
        // cout << roomId << endl;
        // cout << status << endl;
        // cout << endl;

        // 我们要获取到key,value的形式

        //date:1
        string key;
        string value;
        map<string,string>m;

        Sub_info(date,key,value,m); //截取日期
        Sub_info(interval,key,value,m); //截取时间段
        Sub_info(stuId,key,value,m);  // 截取学号
        Sub_info(stuName,key,value,m); // 截取姓名
        Sub_info(roomId,key,value,m); //截取id号
        Sub_info(status,key,value,m); // 截取状态

        // 小map放入到大map容器之中
        this->m_orderData.insert(make_pair(++this->m_Size,m));

    }

    ifs.close();

    // // 调试最大map容器
    // for (auto & it : m_orderData)
    // {
    //     cout << "records number is" << it.first << "value = " << endl;
    //     for(auto & it2 : it.second)
    //     {
    //          cout << " key:" << it2.first << ",value:" << it2.second <<";";
    //     }
    //     cout << endl;

    // }

}

 // 更新预约记录
void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return; // 预约记录0条 直接return

        ofstream ofs(ORDER_FILE,ios::out | ios::trunc); // 先清空文件
        for (int i = 0; i <this->m_Size; ++i)
        {
            ofs << "date:" << this->m_orderData[i]["date"] <<" ";
            ofs << "interval:" << this->m_orderData[i]["interval"] <<" ";
            ofs << "stuId:" << this->m_orderData[i]["stuId"] <<" ";
            ofs << "stuName:" << this->m_orderData[i]["stuName"] <<" ";
            ofs << "roomId:" << this->m_orderData[i]["roomId"] <<" ";
            ofs << "status:" << this->m_orderData[i]["status"] <<" " << endl;
        }

        ofs.close();
    }   
    
}