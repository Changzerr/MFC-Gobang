#pragma once
struct Pieces//�����жϵ�Ԫ
{
	bool bIsPieces;//�Ƿ�������
	bool bIsBlack;//��������
	int x, y;//�������ڸ�
};


//�������㷨����
class CMainGobang
{
public:
	CMainGobang(void);
	~CMainGobang(void);
private:
	/////basic information
	int iSize;//���̴�С����
	int xmax, xmin, ymax, ymin;//���̴�С����
	int idx;//����ÿС�񳤶�
	/////pieces information
	int iPiecesNum;//��������
	Pieces* pPieces;//����
	/////rectangle information
	int iRectangle;//��ǰѡ�п����
	bool NoPieces(int x, int y);//�жϸ�λ�����Ƿ�������
	bool IsBlack(int x, int y);//�жϸ�λ����������ɫ
	bool IsConnect(int iDir, int x, int y);//��������������
	int ConnectNum();//�����������Ӹ���
	
public:
	int iPieces;//���Ӽ���//��ǰ���Ӽ���ΪiPieces-1
	void DrawMainTable(CDC* pDC, CRect rect, int iTableSize);//�������̺���
	void SetPieces();//��κ���//����ʼ��������������̴���ֿ�
	void DrawPieces(CDC* pDC, CRect rect, CPoint pt);//�������Ӻ���
	bool ClearPieces(CDC* pDC, bool& bBlack);//������Ӻ���/���ڻ���
	bool Success();//�ж�ʤ������
	//void ReplayMark(CDC* pDC);//���̱�Ǻ���
};


