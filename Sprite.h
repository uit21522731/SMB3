﻿#pragma once

#include <d3dx9.h>
#include "Graphic.h"
#include "Keyboard.h"
#include "Viewport.h"

class Sprite
{
protected:
	Graphic* SpriteGraphic;//Tạo graphic
	LPDIRECT3DTEXTURE9 Texture;
	char* Pathpng;
	float Width;//Sprite width
	float Height;
	float WidthFrame;
	float HeightFrame;

	int Index = 0;
	float delay;
	int count = 0;	//bộ đếm

	RECT rect;//Hình cần vẽ
	D3DXVECTOR2 position; //vị trí vẽ
	D3DXVECTOR2 center; //vị trí vẽ trong rect
	D3DXVECTOR2 scale; // Vector tùy chỉnh kích thước
	D3DXVECTOR2 transform;
	float angle;	//góc quay theo độ

public:
	Sprite();
	Sprite(Graphic* graphic, const char* pathsprite);
	~Sprite();


	virtual void SetTexture(const char* pathpng);

	virtual float GetWidthFrame();
	virtual float GetHeightFrame();

	virtual RECT GetRect();
	virtual void SetRect(RECT Rect);

	virtual D3DXVECTOR2 GetPosition();
	virtual void SetPosition(D3DXVECTOR2 Position);

	virtual D3DXVECTOR2 GetCenter();
	virtual void SetCenter(D3DXVECTOR2 Center);

	virtual D3DXVECTOR2 GetScale();
	virtual void SetScale(D3DXVECTOR2 Scale);

	virtual D3DXVECTOR2 GetTransform();
	virtual void SetTransform(float x, float y);

	virtual float GetAngle();
	virtual void SetAngle(float Angle);


	virtual void Flip(bool flag);

	virtual void SetData(RECT Rect, D3DXVECTOR2 Center, D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DXVECTOR2 Transform, float Angle);
	virtual void Update(float gameTime, Keyboard* key);
	virtual void Render(Viewport* viewport);
	virtual void Render();
};