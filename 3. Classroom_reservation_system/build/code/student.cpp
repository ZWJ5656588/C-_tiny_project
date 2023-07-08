#include "student.h"

// 默认构造
Student::Student()
{

}

// 有参构造 学号 姓名 密码
Student::Student(int id, string name, string pwd)
{
    // 初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    // 在创建学生时就读取机房信息 使得student可以调用容器 vCom_stu
    // 初始化机房信息 读文件
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_size)  // 将机房信息读取到ComputerRoom对象中
    {
        // 将读取到的信息放入到容器中 通过不断拷贝com
        vComStu.push_back(com);
    }
    
}


// 菜单界面
void Student::operMenu()
{
    cout << "Welcome Student:" << this->m_Name <<  "Login!" <<endl;
    	cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        1. APPLY RESERVATION   |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        2. LOOK UP MY ORDER    |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        3. LOOK UP ALL ORDER   |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        4. CANCEL RESERVATION  |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        0. LOG OUT             |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "Input your choice: ";

}

// 申请预约
void Student::applyOrder()
{
    // 预约 上下午 星期几 机房
    // 需要一个机房容器存储信息 将机房容器添加到student.h中
    // 依然运用读文件的方式把机房信息从文件读到容器中
    cout << "ComputerRoom open days during Monday to Friday" << endl;
    cout << "Please input your application time" << endl;
    cout << "1. Monday"   << endl;
    cout << "2. Tuesday"  << endl;
    cout << "3. Wendsday" << endl;
    cout << "4. Thirsday" << endl;
    cout << "5. Friday"   << endl;

    int date = 0; // 日期
    int interval = 0; //时间段
    int room = 0; //机房编号

    // 输入正确再退出循环
    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "Wrong date,please try again!" << endl;
    }

    cout << "Please input the interval of booking" << endl;
    cout <<"1. Forenoon" << endl;
    cout <<"2. Afternoon" << endl;

    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "Wrong interval,please try again!" << endl;

    }

    cout << "Please select ComputerRoom : " << endl;

    // 用 for循环打印每一个机房信息
    for (int i = 0; i <vComStu.size(); ++i)
    {
        cout << vComStu[i].m_ComId << " Capacity is: " << vComStu[i].m_size << endl;
    }

    while(true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        } 
        cout << "Wrong ComputerRoom info,please try again!" << endl;    
    }

    cout << "Booking success, verifying..." << endl;

    // 将预约信息写入到预约信息文件中
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app); // ios:: app 追加方式写入

    // 将每一项信息写入文件
    ofs << "date:" << date <<" ";
    ofs << "interval:" << interval <<" ";
    ofs << "stuId:" << this -> m_Id << " ";
    ofs << "stuName:" << this -> m_Name << " ";
    ofs << "roomId:" <<  room << " ";
    // 预约状态
    ofs << "status:" << 1 << endl;

    ofs.close();
    system("pause");
    system("cls");


}

// 查看自身预约
void Student::showMyOrder()
{
    // 创建一个查看预约类的对象 调用其默认构造函数
    // 在这个构造函数中 我们把预约信息拿到map容器中,方便下一步查找操作
    OrderFile of; 
    if(of.m_Size == 0)
    {
        cout << "no reservation record!" << endl;
        system("pause");
        system("cls");
        return ;
    }

    for (int i = 1; i <= of.m_Size; i++)
    {
        // string先转成c_str 再转成int 
        // 因为我们在OrderFile的实例对象的构造函数中把信息放入到了map容器中,方便操作
        if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) // 找到自身预约
        {
            cout <<" date of reservation: " << of.m_orderData[i]["date"] << ",";
            cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Forenoon" : "afternoon")<< ",";
            cout << " RoomId: " << of.m_orderData[i]["roomId"] << ",";
            string status = "status:";
            // 1 审核中   2 已预约  -1 预约失败 0 取消预约
            if (of.m_orderData[i]["status"] == "1")
            {
                status += " Under reviewing... ";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "reservation success!";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "faile of reservation,not allowed!";
            }
            else
            {
                status += "reservation cancelled!";
            }
            
        }
        else
        {
            cout << "this student no reservation! " ;
            break;
        }
        
    }
    system("pause");
    system("cls");

    /*atoi这个函数接受一个 C 风格字符串（即以 null 结尾的字符数组），
    并尝试将其解析为整数。解析过程从字符串的第一个非空字符开始，一直到遇到第一个非数字字符为止（包括空格、制表符、换行符等）。如果字符串开头不是数字字符，则返回 0。
    例如，atoi("123") 的返回值为 123，而 atoi("  -123ab") 的返回值为 -123。
    需要注意的是，atoi 函数不会进行错误检查，如果字符串格式不符合要求，会产生未定义行为。因此，为了避免错误，建议使用 std::stoi 函数，它可以进行错误检查，并且支持更多的整数类型。*/
    
}

// 查看所有预约
void Student::showAllrder()
{

}

// 取消预约
void Student::cancelOrder()
{

}
