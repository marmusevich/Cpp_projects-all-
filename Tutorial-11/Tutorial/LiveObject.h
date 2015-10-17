#pragma once
#include <d3dx9.h>

//! Класс живого объекта
class CLiveObject
{
private: // приватные данные
	int m_iHealth; // количество жизней
	D3DXVECTOR2 m_vPos; // позиция на экране
	float m_fRadius; // радиус для столкновений

protected: // защищённые методы, доступ только наследникам
	void Move(float dx, float dy); // сдвинуть на dx, dy
	void Move(const D3DXVECTOR2 delta); // сдвинуть на delta
	void MoveTo(const D3DXVECTOR2 pos); // задать новую позицию

public: // публичные методы класса
	CLiveObject(D3DXVECTOR2 pos, int iHealth=100);
	virtual ~CLiveObject(void); // вирт. деструктор
	void SetHealth(int iHealth);
	int Health() const;
	void DoDamage(const int iDamage); // наносим повреждения
	bool IsAlive() const; // ещё жив (жизней больше 0) ?
	D3DXVECTOR2 Pos() const; // текущая позиция
	float Radius() const; // радиус объекта
	//! функция для проверки столкновения с другим CLiveObject
	bool TestCollision(const CLiveObject& obj) const;
};
