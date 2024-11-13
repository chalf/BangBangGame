#include "BotAIStrategy/TankBehaviorFactory.hpp"

TankBehaviorFactory& TankBehaviorFactory::getInstance() {
    static TankBehaviorFactory instance;
    return instance;
}

void TankBehaviorFactory::registerTankBehavior(int tank, TankBehaviorCreator creator) {
    creators[tank] = creator;
}

TankBehavior* TankBehaviorFactory::createTankBehavior(int tank) {
	/* Phương thức find() của unordered_map:
	Dùng để tìm kiếm một phần tử có key cụ thể trong map.
	Trả về một iterator chỉ đến phần tử được tìm thấy, hoặc iterator đến cuối map nếu không tìm thấy.
	*/
    auto it = creators.find(tank);
    //Nếu tìm thấy
    if (it != creators.end()) {
        return it->second(); // it->second là con trỏ hàm, mà nó là con trỏ hàm nên thêm () để gọi hàm.
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy loại tank
}