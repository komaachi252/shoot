//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�f�o�b�N�\������[Debug.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"
#include "komachi3d.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define DEBUG_CIRCLE_VERTEX_NUM (8)
#define DEBUG_CIRCLE_MAX (256)
#define FVF_DEBUG_CIRCLE_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct DebugCircleVertex_tag {
	D3DXVECTOR4 position;
	D3DCOLOR color;
}DebugCircleVertex;



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static Circle g_Circles[DEBUG_CIRCLE_MAX];
static int g_CircleCount = 0;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;
static D3DCOLOR g_color = 0xFFFFFFFF;
static D3DCOLOR g_colors[DEBUG_CIRCLE_MAX];


//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Debug_Init(void)
{
	g_pDevice = GetDevice();

	g_pDevice->CreateVertexBuffer(DEBUG_CIRCLE_VERTEX_NUM * DEBUG_CIRCLE_MAX * sizeof(DebugCircleVertex), D3DUSAGE_WRITEONLY, FVF_DEBUG_CIRCLE_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	g_pDevice->CreateIndexBuffer((DEBUG_CIRCLE_VERTEX_NUM * 2) * DEBUG_CIRCLE_MAX * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

//��������������������������������������������������������������������������������
//   �J�n����
//��������������������������������������������������������������������������������
void Debug_Begin(void)
{
	g_CircleCount = 0;
}

//��������������������������������������������������������������������������������
//   �`�揈��
//��������������������������������������������������������������������������������
void Debug_DrawCircle(float x, float y, float radius)
{
	if (g_CircleCount >= DEBUG_CIRCLE_MAX ) {
		return;
	}
	
	g_colors[g_CircleCount] = g_color;
	g_Circles[g_CircleCount].position.x = x;
	g_Circles[g_CircleCount].position.y = y;
	g_Circles[g_CircleCount].radius = radius;
	g_CircleCount++;
}
//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Debug_Uninit(void)
{
	if (g_pIndexBuffer) {
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

//��������������������������������������������������������������������������������
//   �I���`�揈��
//��������������������������������������������������������������������������������
void Debug_End(void)
{
	static const float PIZZA = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX_NUM;

	DebugCircleVertex* pV;
	g_pVertexBuffer->Lock(0,0,(void**)&pV, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++) {
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM;
		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++) {
			pV[startIndex + j].position.x = cosf(PIZZA * j) * g_Circles[i].radius + g_Circles[i].position.x;
			pV[startIndex + j].position.y = sinf(PIZZA * j) * g_Circles[i].radius + g_Circles[i].position.y;
			pV[startIndex + j].position.z = 0.0f;
			pV[startIndex + j].position.w = 1.0f;
			pV[startIndex + j].color = g_colors[i];
		}
	}
	g_pVertexBuffer->Unlock();

	WORD* pI;

	g_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);

	for (int i = 0; i < g_CircleCount; i++) {
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM * 2 * i;
		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++) {
			pI[startIndex + j * 2 + 0] = i * startIndex + j;
			pI[startIndex + j * 2 + 1] = i * startIndex + ((j + 1) % DEBUG_CIRCLE_VERTEX_NUM);
		}
	}
	g_pIndexBuffer->Unlock();

	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(DebugCircleVertex));
	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	g_pDevice->SetTexture(0,NULL);

	g_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM, 0, g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM);
}

//��������������������������������������������������������������������������������
//   �F�w�菈��
//��������������������������������������������������������������������������������
void Debug_SetColor(D3DCOLOR color)
{
	g_color = color;
}



