#pragma once
#include <unordered_map>
#include <functional>

#include "TankBehavior.hpp"

class TankBehaviorFactory {
public:
	using TankBehaviorCreator = std::function<TankBehavior*()>;
private:
	//một Map (như Java) nhưng không có thứ tự, 
	//với int là TANKCOLLECTION, còn TankBehaviorCreator  là con trỏ hàm để tạo đối tượng TankBehavior*
    std::unordered_map<int, TankBehaviorCreator> creators;
    TankBehaviorFactory() = default; //Chỉ sử dụng class này để lấy TankBehavior chứ ko cho tạo đối tượng
    TankBehaviorFactory(const TankBehaviorFactory&) = delete; 
    void operator=(const TankBehaviorFactory&) = delete;
    //vẫn cần phải xóa copy constructor và operator= để phòng ngừa friend classes (nếu có) sử dụng
    //Làm như thế để chỉ có một nhà máy mà thôi, đảm bảo singleton

public:
	//lấy instance của factory (giống getFactory)
    static TankBehaviorFactory& getInstance();

    //dùng để đăng ký các TankBehavior
    void registerTankBehavior(int tank, TankBehaviorCreator creator);

    //dùng để lấy TankBehavior từ nhà máy
    TankBehavior* createTankBehavior(int tank);

};
