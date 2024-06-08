﻿#include "Keyboard.h"



Keyboard::Keyboard(/*HINSTANCE Hins,*/ HWND hwnd)
{
	this->Di8 = 0;
	this->DiD8 = 0;
	//this->Hinstance = Hins;
	this->Hwnd = hwnd;
	ZeroMemory(&this->key_buffer, sizeof(this->key_buffer));
}

Keyboard::~Keyboard()
{
}

//Cài đặt bàn phím
bool Keyboard::Init()
{
	HRESULT hr = DirectInput8Create(
		/*this->Hinstance,*/	//Hinstance của chương trình
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,//Tham số mặc định
		IID_IDirectInput8,
		(void**)&this->Di8,//Con trỏ nhận dữ liệu trả về
		NULL);//Tham số thêm

	if (FAILED(hr))
	{
		return false;
	}
	
	//Tạo bàn phím GUID_SysKeyboard
	hr = this->Di8->CreateDevice(GUID_SysKeyboard, &this->DiD8, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	
	//Dạng dữ liệu được nhận
	hr = this->DiD8->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}
	
	//Loại hoạt động 
	hr = this->DiD8->SetCooperativeLevel(this->Hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); //DISCL_FOREGROUND chỉ hoạt động khi của sổ hWnd đang được handle
	if (FAILED(hr))
	{
		return false;
	}
	
	//Yêu cầu thiết bị
	hr = this->DiD8->Acquire();
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//Lấy trạng thái bàn phím
void Keyboard::GetStage()
{
	HRESULT hr = this->DiD8->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	
	//Nếu bàn phím nhả ra yêu cầu nhập lại
	if (FAILED(hr))
	{
		while (this->DiD8->Acquire() == DIERR_INPUTLOST);
	}
}

//Nhận diện phím nhấn
bool Keyboard::IsKeyDown(int key)
{
	//Trả về phím có được nhấn hay không
	return key_buffer[key] & 0x80;//0x80 xác định bit đầu tiên
}

//Kiểm tra trạng thái phím có đang down
bool Keyboard::GIsKeyDown(int key)
{
	return (IsKeyDown(key));
}

//Kiểm tra trạng thái phím có đang up
bool Keyboard::GIsKeyUp(int key)
{
	return (!(IsKeyDown(key)));
}

//Hủy phím
void Keyboard::KillKeyboard()
{
	if (DiD8 != NULL)
	{
		this->DiD8->Unacquire();
		this->DiD8->Release();
		this->DiD8 = NULL;
	}
}