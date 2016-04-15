/*
为以下Programmer对象提供一个基于Id并且升序的仿函数ProgrammerIdGreater，使得Programmer对象可以在set中以Id 排序存放。
(1) 将Programmer(1, L"Scott Meyers")、Programmer(2, L"MartinFowler")、Programmer(3, L"Bill Gates")、Programmer(4, L"P.J.Plaught")、Programmer(5, L"Stanley B. Lippman")、Programmer(6, L"Andrei Alexandrescu")插入到一个set 中；
(2) 通过for_each 遍历set，并且使用Programmer 对象的Print 方法打印出对象，结果应该如下所示；

[6] : Andrei Alexandrescu
[5] : Stanley B. Lippman
[4] : P.J. Plaught
[3] : Bill Gates
[2] : Martin Fowler
[1] : Scott Meyers

(3) 在set 中查找Id 为3、名称为“Bill Gates”的对象；
(4) 如果(2)中找到目标对象，则将其名称改成“David Vandevoorde”，再通过for_each 重新打印set，查看是否真的修改成功了；
(5) 重新定义一个set(命名为set2)，将Programmer 在set2 中排序方式改为通过Name 来排序，为此还需重新定义一个仿函数用于比较Name，请写出该仿函数，名字可能类似ProgrammerNameComparer;
(6) 通过for_each 重打印set2，验证set2 中的元素是否是按照名字来排序的。

struct Programmer
{
    Programmer(const int id, const std::wstring name)
        : Id(id), Name(name)
    {
    }
    void Print() const
    {
        std::wcout << L"[" << Id << L"] : " << Name << std::endl;
    }
    int Id;
    std::wstring Name;
};
struct ProgrammerIdGreater { ... }
*/
struct Programmer{
    Programmer(const int id, const std::wstring name):
         Id(id), Name(name){  }

    void Print() const 
    {
        std::wcout<<L"["<<Id<<L"]: "<<Name<<std::endl;
    }

    int Id;
    std::wstring Name;
};



//2, 定义仿函数

//a, 使用ID升序排序
struct ProgrammerIdGreater : public std::binary_function< Programmer, Programmer, bool>{
    bool operator() (const Programmer& p1, const Programmer& p2) const {
    return (key1 <= key2) ? false : true;
    }
};

//b, 使用Name来进行排序
struct ProgrammerNameComparer : public std::binary_function< Programmer, Programmer, bool>{
    bool operator() (const Programmer& p1, const Programmer& p2) const {
    return (p1.GetId() <= p2.GetId()) ? false : true;
    }
};


void main()
{

    //构建数组
    Programmer vp[6] = {
        Programmer("Andrei", 6),
        Programmer("Stanley", 5),
        Programmer("Plaught", 4),
        Programmer("BillGates", 3),
        Programmer("Fowler", 2),
        Programmer("Meyes", 1)
    };
    //构建set
    std::set<Programmer, ProgrammerIdGreater > dest(vp, vp+6);

    //遍历set
    std::for_each( dest.begin(), dest.end(), std::mem_fun(&Programmer::Print) );

    //将dest中的BillGates改为David
    std::set<Programmer, ProgrammerIdGreater>::iterator it = dest.find(Programmer("BillGates", 3));
    if(it != dest.end())
        const_cast<Programmer&>(*it).SetName("David");

    //遍历set
    std::for_each( dest.begin(), dest.end(), std::mem_fun(&Programmer::Print) );

    //新set2用名字排序
    std::set<Programmer, ProgrammerNameComparer > dest2(dest, dest+6);

    //遍历set2
    std::for_each( dest2.begin(), dest2.end(), std::mem_fun(&Programmer::Print) );


}





