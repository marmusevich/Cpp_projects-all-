#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Graphics;

class CShader
{
	friend class Graphics;

private:
	//! ��� ���������� ������?
	bool m_bIsPS;
	//! ����� ������ ���������
	LPD3DXBUFFER m_pErrors;
	//! ����� �������������� ������
	LPD3DXBUFFER m_pShaderBuff;
	//! ������� �������� �������
	LPD3DXCONSTANTTABLE m_pConstTable;
	//! ���������� � ��������� ������. �������� ������
	union
	{
		LPDIRECT3DPIXELSHADER9 m_pPixelShader;
		LPDIRECT3DVERTEXSHADER9 m_pVertexShader;

	} m_pShader;

	//! ������, � ������� ������ ������
	LPDIRECT3DDEVICE9 m_pShaderDevice;

protected:
	//! ������� �������� � ���������� �������
	HRESULT Load( const std::string& strFileName, const std::string& strFuncName, const std::string& profile);
	HRESULT Release();
	//! ��������� ����������� �������
	LPDIRECT3DPIXELSHADER9 GetPixelShader();
	//! ��������� ����������� �������
	LPDIRECT3DVERTEXSHADER9 GetVertexShader();
	//! ��������� ������ ���������������� ������� (����� ��� �������� HW-�������)
	LPD3DXBUFFER GetCompileBuffer();
	//! ��������� HW-������� (�����������)
	void SetHardwareShader(LPDIRECT3DDEVICE9 pDev, LPDIRECT3DPIXELSHADER9 pHWShader);
	//! ��������� HW-������� (�����������)
	void SetHardwareShader(LPDIRECT3DDEVICE9 pDev, LPDIRECT3DVERTEXSHADER9 pHWShader);
	CShader(void);
	~CShader(void);

public:
	bool IsPS(); // ��� ���������� ������?
	bool IsVS(); // ��� ��� ���������� ������?
	//! ������� ������� �������
	HRESULT SetFloat(D3DXHANDLE hConstant, CONST FLOAT Value);
	HRESULT SetVector(D3DXHANDLE hConstant, CONST D3DXVECTOR4* pVec4);
	HRESULT SetMatrix(D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix);
};

typedef CShader* CShaderPtr; // ��� ���������� �� ��������