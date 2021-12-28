#include "pch.h"
#include "GobangHandle.h"
#include "GobangHandle.h"


CMainGobang::CMainGobang(void)
{
	//AfxMessageBox(_T("����ִ���˹��캯��"));
}


CMainGobang::~CMainGobang(void)
{
	//AfxMessageBox(_T("����ִ������������"));
}

//�������̺���
//���ڿ�������̴�С����
//�ؼ�����
void CMainGobang::DrawMainTable(CDC* pDC, CRect rect, int iTableSize)
{
	iSize = iTableSize;
	//�ȸ��Ǳ���
	CRect Back;
	Back.top = rect.top + 1;
	Back.bottom = rect.bottom - 1;
	Back.left = rect.left + 1;
	Back.right = rect.right - 1;
	pDC->FillSolidRect(&Back, RGB(171, 171, 171));//���
	//����ÿ�񳤶�ȡС��Ϊ����
	idx = (((rect.right - rect.left) / (iTableSize + 1)) > ((rect.bottom - rect.top) / (iTableSize + 1))) ?
		(rect.bottom - rect.top) / (iTableSize + 1) :
		(rect.right - rect.left) / (iTableSize + 1);
	CBrush brush(RGB(0, 0, 0));
	CBrush* OldBrush = (CBrush*)pDC->SelectObject(&brush);
	int ixp, iyp;//����������
	//������Ԫ�����ĵ㣩
	ixp = (rect.right - rect.left) / 2;
	iyp = (rect.bottom - rect.top) / 2;
	pDC->Ellipse(ixp - 3, iyp - 3, ixp + 3, iyp + 3);
	//�����ǣ��ĸ�Բ�㣩
	ixp -= 4 * idx;
	iyp -= 4 * idx;//���Ͻ�
	pDC->Ellipse(ixp - 3, iyp - 3, ixp + 3, iyp + 3);
	iyp += 8 * idx;//���½�
	pDC->Ellipse(ixp - 3, iyp - 3, ixp + 3, iyp + 3);
	ixp += 8 * idx;//���½�
	pDC->Ellipse(ixp - 3, iyp - 3, ixp + 3, iyp + 3);
	iyp -= 8 * idx;//���Ͻ�
	pDC->Ellipse(ixp - 3, iyp - 3, ixp + 3, iyp + 3);
	pDC->SelectObject(OldBrush);//�ָ��豸������ԭ���Ļ���
	brush.DeleteObject();//�ͷŻ�ͼ��Դ
	//�������̴�С�������ڴ����м�
	ymin = (rect.bottom - rect.top) / 2 - (iTableSize - 1) / 2 * idx;
	ymax = ymin + (iTableSize - 1) * idx;
	xmin = (rect.right - rect.left) / 2 - (iTableSize - 1) / 2 * idx;
	xmax = xmin + (iTableSize - 1) * idx;
	for (int x = xmin; x <= xmax; x += idx)
	{
		pDC->MoveTo(x, ymin);
		pDC->LineTo(x, ymax);
	}
	for (int y = ymin; y <= ymax; y += idx)
	{
		pDC->MoveTo(xmin, y);
		pDC->LineTo(xmax, y);
	}
}

//��κ���
void CMainGobang::SetPieces()
{
	iPiecesNum = iSize * iSize;//�����жϵ�Ԫ��
	iPieces = 0;//���Ӽ���
	pPieces = new Pieces[iPiecesNum];//���ɴ洢�����ж�
	for (int i = 0; i < iPiecesNum; i++)
	{
		pPieces[i].bIsPieces = false;//Ĭ�ϸ�λ��û������
		if (i % 2 != 0)
		{
			pPieces[i].bIsBlack = false;//˫��Ϊ������
		}
		else
		{
			pPieces[i].bIsBlack = true;//����Ϊ������
		}
	}
}


//�������Ӻ���
void CMainGobang::DrawPieces(CDC* pDC, CRect rect, CPoint pt)
{
	int iColor;
	if (pPieces[iPieces].bIsBlack == true)//������
	{
		iColor = 0;
	}
	if (pPieces[iPieces].bIsBlack == false)//������
	{
		iColor = 255;
	}
	//��ȡ�����λ����������
	int x, y;//�������
	int iTmp;
	iTmp = int(double(pt.x - xmin) / idx + 0.5);
	x = iTmp < 0 ? xmin : xmin + iTmp * idx;//��������������
	iTmp = int(double(pt.y - ymin) / idx + 0.5);
	y = iTmp < 0 ? ymin : ymin + iTmp * idx;
	x = x > xmax ? xmax : x;
	y = y > ymax ? ymax : y;
	if (NoPieces(x, y))
	{
		//������
		CBrush brush;
		brush.CreateSolidBrush(RGB(iColor, iColor, iColor));
		CBrush* OldBrush = (CBrush*)pDC->SelectObject(&brush);
		pDC->Ellipse(x - 10, y - 10, x + 10, y + 10);
		pDC->SelectObject(OldBrush);//�ָ��豸������ԭ���Ļ���
		brush.DeleteObject();//�ͷŻ�ͼ��Դ
		
		//��ֵ
		pPieces[iPieces].bIsPieces = true;
		pPieces[iPieces].x = x;
		pPieces[iPieces].y = y;
		//������1
		iPieces++;
	}
}

//������Ӻ���/���ڻ���
bool CMainGobang::ClearPieces(CDC* pDC, bool& bBlack)
{
	CRect rect;
	if (pPieces[0].bIsPieces)
	{
		rect.bottom = pPieces[iPieces - 1].y + 10;
		rect.top = pPieces[iPieces - 1].y - 10;
		rect.left = pPieces[iPieces - 1].x - 10;
		rect.right = pPieces[iPieces - 1].x + 10;
		pDC->FillSolidRect(&rect, RGB(171, 171, 171));//���

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* OldPen = pDC->SelectObject(&pen);
		pDC->MoveTo(pPieces[iPieces - 1].x, pPieces[iPieces - 1].y - 10);
		pDC->LineTo(pPieces[iPieces - 1].x, pPieces[iPieces - 1].y + 10);
		pDC->MoveTo(pPieces[iPieces - 1].x - 10, pPieces[iPieces - 1].y);
		pDC->LineTo(pPieces[iPieces - 1].x + 10, pPieces[iPieces - 1].y);
		pDC->SelectObject(OldPen);//�ָ��豸������ԭ���Ļ���
		pen.DeleteObject();//�ͷŻ�ͼ��Դ

		pPieces[iPieces - 1].x = NULL;
		pPieces[iPieces - 1].y = NULL;
		pPieces[iPieces - 1].bIsPieces = false;
		if ((iPieces - 1) % 2 == 0)
		{
			bBlack = false;
		}
		else
		{
			bBlack = true;
		}
		iPieces--;//������1
		return true;
	}
	else
	{
		return false;
	}
}


//�жϸ�λ�����Ƿ�������
bool CMainGobang::NoPieces(int x, int y)
{
	//�����Ӹ�������0
	if (iPieces > 0)
	{
		for (int i = 0; i < iPieces; i++)
		{
			if ((x == pPieces[i].x) && (y == pPieces[i].y))//û������ʱ��pPieces��x,y��Ϊ��ֵ
			{
				if (pPieces[i].bIsPieces)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
	return true;
}

//�жϸ�λ����������ɫ
bool CMainGobang::IsBlack(int x, int y)
{
	for (int i = 0; i < iPiecesNum; i++)
	{
		if ((x == pPieces[i].x) && (y == pPieces[i].y))
		{
			if (!pPieces[i].bIsBlack)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	
	return true;
}

//��������������
//up1,down2,left3,right4,up-left5,down-right6,up-right7,down-left8
bool CMainGobang::IsConnect(int iDir, int x, int y)
{
	bool bIsConnect = false;
	if (((iDir == 1) && (IsBlack(x, y) == IsBlack(x, y - idx)) && (!NoPieces(x, y - idx)))//���ϲ���
		|| ((iDir == 2) && (IsBlack(x, y) == IsBlack(x, y + idx)) && (!NoPieces(x, y + idx)))//���²���
		|| ((iDir == 3) && (IsBlack(x, y) == IsBlack(x - idx, y)) && (!NoPieces(x - idx, y)))//�������
		|| ((iDir == 4) && (IsBlack(x, y) == IsBlack(x + idx, y)) && (!NoPieces(x + idx, y)))//���Ҳ���
		|| ((iDir == 5) && (IsBlack(x, y) == IsBlack(x - idx, y - idx)) && (!NoPieces(x - idx, y - idx)))//�����ϲ���
		|| ((iDir == 6) && (IsBlack(x, y) == IsBlack(x + idx, y + idx)) && (!NoPieces(x + idx, y + idx)))//�����²���
		|| ((iDir == 7) && (IsBlack(x, y) == IsBlack(x + idx, y - idx)) && (!NoPieces(x + idx, y - idx)))//�����ϲ���
		|| ((iDir == 8) && (IsBlack(x, y) == IsBlack(x - idx, y + idx)) && (!NoPieces(x - idx, y + idx))))//�����²���
	{
		bIsConnect = true;
	}
	return bIsConnect;
}

//�����������Ӹ���
int CMainGobang::ConnectNum()
{
	int iConnect;//����������
	int iGetNum;//����������
	int icx, icy;//����λ�ƿ�����
	int iTmp;//�м����
	//���᷽��***************
	iGetNum = iConnect = 1;
	icy = 0;
	while (iGetNum < 5)//���ϲ���5��
	{
		if (IsConnect(1, pPieces[iPieces - 1].x, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum = 1;
	icy = 0;
	while (iGetNum < 5)//�����²���
	{
		if (IsConnect(2, pPieces[iPieces - 1].x, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp = iConnect;
	//���᷽��****************
	iGetNum = iConnect = 1;
	icx = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(3, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y))
		{
			iConnect++;
			icx--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum = 1;
	icx = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(4, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y))
		{
			iConnect++;
			icx++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp = max(iTmp, iConnect);
	//����-���·���****************
	iGetNum = iConnect = 1;
	icx = icy = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(5, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icx--;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum = 1;
	icx = icy = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(6, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icx++;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iTmp = max(iTmp, iConnect);
	//����-���·���****************
	iGetNum = iConnect = 1;
	icx = icy = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(7, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icx++;
			icy--;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iGetNum = 1;
	icx = icy = 0;
	while (iGetNum < 5)
	{
		if (IsConnect(8, pPieces[iPieces - 1].x + icx * idx, pPieces[iPieces - 1].y + icy * idx))
		{
			iConnect++;
			icx--;
			icy++;
		}
		else
		{
			break;
		}
		iGetNum++;
	}
	iConnect = max(iTmp, iConnect);
	return iConnect;
}

//�ж��Ƿ�ʤ��
bool CMainGobang::Success()
{
	bool bSuccess;
	bSuccess = false;
	if (ConnectNum() >= 5)
	{
		if (pPieces[iPieces - 1].bIsBlack)
		{
			AfxMessageBox(_T("����ʤ��!"));
		}
		if (!pPieces[iPieces - 1].bIsBlack)
		{
			AfxMessageBox(_T("����ʤ��!"));
		}
		bSuccess = true;
	}
	return bSuccess;
}


////���̱�Ǻ���
//void CMainGobang::ReplayMark(CDC* pDC)
//{
//	CString strNum;//���ֱ��
//	//�趨����
//	CFont m_newFont;//������������ַ���������
//	CFont* m_OldFont;//���ڻ�ԭԭ��������
//	m_newFont.CreatePointFont(80, _T("����"));//�������壬8*n�����ظߵ�����
//	m_OldFont = (CFont*)pDC->SelectObject(&m_newFont);//�����帳���豸������
//	pDC->SetBkMode(TRANSPARENT);//�����������ı���͸��
//	//�������ֵ����ͼ�ؼ�
//	for (int i = 0; i < iPieces; i++)
//	{
//		strNum.Format(_T("%d"), i + 1);
//		if (i % 2 == 0)
//		{
//			pDC->SetTextColor(RGB(255, 255, 255));//����������ɫ
//		}
//		else
//		{
//			pDC->SetTextColor(RGB(0, 0, 0));//����������ɫ
//		}
//		pDC->TextOut(pPieces[i].x - 5, pPieces[i].y - 5, strNum);
//	}
//	pDC->SelectObject(m_OldFont);//�ָ�ԭ����
//	if (pPieces != NULL)
//	{
//		delete[]pPieces;
//		pPieces = NULL;
//	}
//	if (pmyRectangle != NULL)
//	{
//		delete[]pmyRectangle;
//		pmyRectangle = NULL;
//	}
//}
