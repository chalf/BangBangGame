#pragma once
#include <stdio.h>
#include <string>

#include "Tank.hpp"

class Tank;

class Bullet
{
private:
    SDL_Texture* texture;	//hình ảnh của đạn
    //kiểm soát việc ko thể xuất hiện nhiều hơn 1 viên đạn khi bắn, active = true tức là đạn đang tồn tại
	bool active;	//nếu bay chưa hết tầm
	bool touch;		// nếu chạm vật cản
	/*lý do tách thành 2 biến bool thay vì 1: vì mục đích là trong 1 khoảng thời gian nhất định thì tank không thể bắn, cho đến khi đạn bay vượt tầm hoặc chạm vật cản, như thế sẽ đảm bảo tốc độ bắn của tank là cố định
	nhưng có vấn đề: khi đạn bay quá tầm bắn mất 2s, nhưng khi nó chạm vật cản -> nó sẽ mất 1s từ đó, 
	nếu tank đứng càng gần vật cản thì thời gian đạn từ lúc đc bắn đến khi chạm vật cản sẽ càng nhanh hơn 1s (tức là nhỏ hơn 1s), 
	từ đó sẽ có lỗi logic, người chơi có thể lợi dụng điều này để tăng tốc độ bắn của tank,
	thay vì mỗi 2s bắn 1 lần, thì bây giờ chỉ cần đứng sát vật cản mỗi lần bắn chỉ cách nhau chưa tới 1s */

    SDL_Rect rect;	//vị trí và kích thước
    int initPosX, initPosY;	//lưu vị trí ban đầu để tính toán đạn đã bay được bao xa
    float angle; //góc xoay theo hướng con trỏ chuột
    //bộ va chạm của đạn
    std::vector<SDL_Rect> colliders;
    bool wasShot;
    /*mục đích: khi collider của đạn chạm collider của tank thì sẽ trừ máu tank,
    nhưng 1 tank có một bộ collider gồm nhiều rect, nên phải kiểm soát chỉ trừ máu 1 lần */

    void loadTexture(SDL_Renderer* renderer, std::string path);
    void shiftColliders();
public:
	//tạo bullet và gán width và height cho texture 
	Bullet(SDL_Renderer* renderer, std::string imagePath, std::vector<SDL_Rect> colliders);
	void fly(const int bulletSpeed, const int range, std::vector<Tank*> enemyTanks, std::vector<SDL_Rect> mapColliders, float deltaTime);
	void clean();

	//getter
	SDL_Texture* getTexture();
	bool isActive();
	void setActive(bool flag);
	bool isTouch();
	void setTouch(bool flag);
	SDL_Rect getRect();
	void setRect(SDL_Rect rect);
	void setInitPos(int x, int y);
	//lấy width và height của đạn từ rect
	int getWidth();	
	int getHeight();

	float getAngle();
	void setAngle(float angle);
	std::vector<SDL_Rect>& getColliders();
};