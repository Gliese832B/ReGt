#pragma once

#include <stdio.h>
#include "Manager/VariantDB.h"
#include "Entity/Entity.h"
#include "Entity/EntityUtils.h"
#include "cloud.h"
Entity* AddBMPRectAroundEntity(Entity* pParentEnt, int backgroundColor, int borderColor, float padding, bool UseUpWhite, float scale, eFont font) {
		CL_Vec2f pos2d; 
		CL_Vec2f size2d;
		CL_Vec2f v57;
		CL_Vec2f v58; // [sp+98h] [bp-38h] BYREF
		CL_Vec2f v59; // [sp+A0h] [bp-30h] BYREF
		Entity* pOverlayEnt;
		//thanks ýprog
		int v14;
		float scalebumbum;
		float scaledeneme;
		eAlignment entityalignment;
		scalebumbum = 292 * font + 504;
		float y;
		pos2d = GetPos2DEntity(pParentEnt);
		size2d = GetSize2DEntity(pParentEnt);
		CL_Vec2f vSize = pParentEnt->GetVar("size2d")->GetVector2();

	
		y = size2d.y;
		RTFont RTFont;
		float lineHeight = GetBaseApp()->GetFont(font)->GetLineHeight(scale);
		if (y <= lineHeight) {
			scaledeneme = lineHeight;
		
		}
		else {
			scaledeneme = y;
		}
		y = scaledeneme;
		entityalignment = GetAlignmentEntity(pParentEnt);
		v57 = GetAlignmentOffset(size2d, entityalignment);
	
		size2d.x = (float)(padding + padding) + size2d.x;
		size2d.y = (float)((float)(padding * 0.6) * 3.0) + size2d.y;
		pos2d.x = (float)(pos2d.x - v57.x) - padding;
		v14 = *((DWORD*)pParentEnt + 26);
		pos2d.y = (float)(pos2d.y - v57.y) - (float)(padding * 0.6);
		v58 = pos2d;
		v59 = size2d;
		pOverlayEnt = CreateOverlayRectEntity(pParentEnt->GetParent(), v58, v59, backgroundColor);
		if (UseUpWhite) {
		
			EntityComponent* v29 = pOverlayEnt->GetComponentByName("RectRender");
			
		
			Variant* v73 = v29->GetVar("bmpBorderFileName");
			v73->Set("game/gui_box_upwhite.rttex");
			// FunctionObject* Onbutton = pOverlayEnt->GetComponentByName("RectRender")->GetFunction("OnButtonSelected");


	

		}
		else {
			EntityComponent* v29 = pOverlayEnt->GetComponentByName("RectRender");
			Variant* v73 = v29->GetVar("bmpBorderFileName");
			v73->Set("game/gui_box_white.rttex");
		}
		pOverlayEnt->GetComponentByName("RectRender")->GetVar("borderColor")->Set(uint32(borderColor));
	
		pOverlayEnt->SetName("BGRect");
		pParentEnt->GetParent()->MoveEntityToBottomByAddress(pOverlayEnt);
		return pOverlayEnt;

	}
struct Background;
struct Cloud
{
	float field_0;
	float field_4;
	int field_8;
	int field_C;
	float field_10;
	int field_14;
	int field_18;
	void Init(Background* bk);
	void Update(Background* bk);
};

struct Background {
	
	SurfaceAnim surfacean1;
	
	SurfaceAnim surfacean2;
	SurfaceAnim surfacean3;
	SurfaceAnim surfacean4;
	bool v4;
	SurfaceAnim m_surf_sun;
	Surface* m_hills;
	SurfaceAnim m_surf_cloud;
	Cloud* m_clouds;
	 // r0
	int m_num_clouds;
	int idx; // r5
	unsigned int idx2; // r6
	void InitClouds(int num_clouds);
	unsigned int fieldcc;
	
	unsigned int fieldd;
	
	
	int field8;
	Background();
	void SortClouds();
	void Render(CL_Vec2f vec, float graphics_detail);
	void DrawHill(int hillnumbers, CL_Vec2f* a3);
	void Update();
	float derinlik;
	float randomsayýidk;
	float randomsayýidk2;
	float m_Scale_X, m_Scale_Y;
	int field_14;
	CL_Rectf* field_4 = new CL_Rectf(GetScreenRect());
	CL_Rectf *v5;
	float field_0;
	float v6;
	CL_Rectf* v7;
	
	int field_c;
	int v9;
	float v10;
	int field_8;
	unsigned int result;
	int field_18;
	
};

void Cloud::Init(Background* bk) {
	


	bool v4; // r0
	CL_Rectf* v5; // r3
	float v6; // r0
	CL_Rectf* v7; // r7
	float v8; // r0
	float v9; // r0
	float v10; // r5
	unsigned int result;
	field_10 = RandomRangeFloat(0.1, 1.0);
	

	v4 = RandomRangeFloat(0.0, 1.0) < 0.5;
	if (v4)
		field_14 = 1;
	v5 = bk->field_4;
	if (!v4)
		field_14 = 0;
	v6 = RandomRangeFloat(0.0, (float)(v5->right - v5->left) / field_10);
	v7 = bk->field_4;
	field_0 = v6 + (float)(v7->left / field_10);
	v8 = (RandomRangeFloat(0.0, (float)((float)(v7->bottom - v7->top) * 0.5) / field_10))
		+ (float)(bk->field_4->left) / field_10;

	field_C = 0;
	field_4 = v8;
	v9 = RandomRangeFloat(-0.05, -1.0);
	v10 = field_10;
	field_8 = v9;
	result = (unsigned int)(float)(v10 * 13.0) + 242;
	field_18 = (((unsigned int)(float)(v10 * 159.0) + 96) << 8)
		+ (((unsigned int)(float)(v10 * 40.0) + 215) << 16)
		+ 255
		+ (result << 24);

}
void Cloud::Update(Background* bk) {
	int v4; // r7
	float v5; // r6
	float v6; // r0
	float v7; // r7
	CL_Rectf* v8; // r6
	 // r10
	float v10; // r8
	float result; // r0
	v4 = field_8;
	v5 = field_0;
	v6 = v5 + v4 * (GetBaseApp()->GetGameTimer()->GetDelta());
	v7 = field_10;
	field_0 = v6;
	v8 = bk->field_4;
	
	if (v6 < (float)((float)(v8->left - (float)((float)(bk->m_Scale_X * 197.0) * v7)) / v7)
		|| v6 > (float)((float)(v8->left + (float)((float)(v8->right - v8->left) * 1.4)) / v7))

	
	{
		
		Init(bk);
		result = bk->field_4->left + bk->field_4->top - bk->field_4->left * 1.2
			/ field_10; //birþeyler tersse buraya bak hata olabilir
		field_0 = result;
	}

	Init(bk);
	
}

void Background::Update() {
	Cloud* v2; // r0
	int v3; // r5
	unsigned int v4; // r6

	v2 = m_clouds;
	if (v2 && m_num_clouds)
	{
		v3 = 0;
		v4 = 0;
		while (1)
		{
			Cloud cloud;
			v2[v3].Update(this);
			++v4;
			++v3;
			if (m_num_clouds <= v4)
				break;
			v2 = m_clouds;
			
		}
	}
}
void Background::InitClouds(int num_clouds) {
	Cloud* m_clouds;
	Cloud* m_old_clouds;
	int m_num_clouds; // r3
	int idx; // r5
	unsigned int idx2; // r6
	m_old_clouds = this->m_clouds;
	this->m_num_clouds = num_clouds;
	if (m_old_clouds)
	{
		delete[](m_old_clouds);
		num_clouds = this->m_num_clouds;
		this->m_clouds = 0;
	}
	m_clouds = new Cloud[num_clouds];
	m_num_clouds = this->m_num_clouds;
	this->m_clouds = m_clouds;
	if (m_num_clouds)
	{
		idx = 0;
		idx2 = 0;
		while (1)
		{
			
			m_clouds[idx].Init(this);
			++idx2;
			++idx;
			if (this->m_num_clouds <= idx2)
				break;
			m_clouds = this->m_clouds;
		}
	}
	}
  Background::Background() {
	  m_clouds = new Cloud[5];
	  field_c = 0.0f;
	  field_8 = 0.0f;

	  m_surf_sun.LoadFile("cache/game/sun.rttex");
	  m_surf_sun.SetupAnim(1, 1);

	  m_hills = new Surface[3];
	  m_hills[0].LoadFile("cache/game/hills3.rttex");
	  m_hills[1].LoadFile("cache/game/hills2.rttex");
	  m_hills[2].LoadFile("cache/game/hills1.rttex");

	  m_surf_cloud.LoadFile("cache/game/cloud.rttex");
	  m_surf_cloud.SetupAnim(1, 1);

	  
	  field_8 = 1.0f;
	  field_c = 1.0f;

	fieldcc = 50;
	fieldd = 0;
	field8 = 0;
	m_Scale_X = 1.0f;
	m_Scale_Y = 1.0f;
	
	
	/*field_4->right = 0;
	field_4->left = 0;
	field_4->top = 0;
	field_4->right = 1065353216;
	field_4->top = 1065353216;
 */




}
  
  
  
  void Background::Render(CL_Vec2f vec, float graphics_detail) {
	  CL_Vec2f sun_rot_offs; // [sp+90h] [bp-50h] BYREF
	  CL_Vec2f sun_scale_vec; // [sp+98h] [bp-48h] BYREF
	  unsigned __int8 v8;
	  int cloud_idx, cloud_idx_2, v25;
	  float sun_scale;
	  Cloud* v11;
	  float v12;
	  float v23, v22;
	  float v7;
	  
	  int hill_number;
	  float a2;
	  float v13;
	  int a8;
	  CL_Vec2f v31;
	  CL_Vec2f v32;
	  float v15;
	  float v16;
	  float v17;
	  CL_Vec2f v27; // [sp+60h] [bp-80h] BYREF
	  CL_Vec2f v28; // [sp+68h] [bp-78h] BYREF
	  CL_Vec2f v29; // [sp+70h] [bp-70h] BYREF
	  CL_Vec2f v30;
	  float v19;
	  int v20;
	  
	  CL_Rectf r = GetScreenRect();
	 
	  DrawFilledRect(r, 0xF2D760FF);
	  if (graphics_detail <= 0.1)
		  return;
	  CL_Vec2f a1 = GetScreenSize();
	  
	  sun_scale = (float)(a1.x / 161.0) / 6.0;
	  CL_Vec2f v36 = GetScreenSize();
	  v7 = v36.x * 0.7;
	  CL_Vec2f v35 = GetScreenSize();
	  v8 = 0;
	  sun_scale_vec.y = sun_scale;
	  sun_scale_vec.x = sun_scale;
	  sun_rot_offs.x = 0.0;
	  sun_rot_offs.y = 0.0;

	  m_surf_sun.BlitScaledAnim(v7, v35.y * 0.1, 0, 0, sun_scale_vec, ALIGNMENT_UPPER_LEFT, -1, 0, sun_rot_offs, 0, 0);
	  if (!m_clouds)
		  return;
	 
	  if (graphics_detail <= 0.4 || !this->m_num_clouds)
	  {
		  hill_number = 0;
		  goto LABEL_23;
	  }
	  if (graphics_detail > 0.8)
		  v8 = 1;
	  cloud_idx = 0;
	  v25 = v8;
	  cloud_idx_2 = 0;
	  hill_number = 0;

	  do {
		  v11 = &this->m_clouds[cloud_idx];
		  v12 = v11->field_10;
		  a2 = (float)(v12 * v11->field_0) - vec.x;
		  v23 = (float)(v12 * v11->field_4) - vec.y;
		  v22 = v12 * this->m_Scale_X;
		  v13 = v12 * this->m_Scale_Y;
		  if (v25) {
			  v13 = v12 * this->m_Scale_Y;
			  a8 = (int)(float)(v12 * 255.0) - 256;
			  v11->field_18 = a8;

		  }
		  else
		  {
			  a8 = v11->field_18;
		  }
		  v31.y = v13;
		  v31.x = v22;
		  v32.x = 0.0;
		  v32.y = 0.0;
		  m_surf_cloud.BlitRotatedAnim(a2, v23, 0, 0, v31, ALIGNMENT_DOWN_LEFT, a8, 0, v32, v11->field_14, 0);
		  
		  if (hill_number)
		  {
			  if (hill_number != 1)
			  {
				  if (hill_number != 2)
					  goto LABEL_20;		
				  goto LABEL_17;
			  }
		  }
		  else {
			  if (this->m_clouds[cloud_idx].field_10 <= 0.2) {
				  goto LABEL_21;
			  }
			  v15 = vec.y;
			  v30.x = vec.x;
			  v30.y = v15;
			  Background::DrawHill(0, &v30);
		  }
		  if (this->m_clouds[cloud_idx].field_10 <= 0.4) {
			  hill_number = 1;
			  goto LABEL_21;
		  }
		  v16 = vec.y;
		  v29.x = vec.x;
		  v29.y = v16;
		  Background::DrawHill(1, &v29); 
	  LABEL_17:
		  if (this->m_clouds[cloud_idx].field_10 <= 0.6) {
			  hill_number = 2;
			  goto LABEL_21;

		  }

		  v17 = vec.y;
		  v28.x = vec.x;
		  v28.y = v17;
		  Background::DrawHill(2, &v28);
	  LABEL_20:
		  hill_number = 3;
	  LABEL_21:
		  ++cloud_idx;
	  } while (this->m_num_clouds > (unsigned int)++cloud_idx_2);







		  while (this->m_num_clouds > (unsigned int)++cloud_idx_2);
		  if (hill_number != 3)
		  {
			  do
			  {
			  LABEL_23:
				  v19 = vec.y;
				  v20 = hill_number++;
				  v27.x = vec.x;
				  v27.y = v19;
				  Background::DrawHill(v20, &v27);
			  } 
			  while (hill_number <= 2);
		  }
	  


  }
void Background::DrawHill(int hillnumbers, CL_Vec2f* a3) {
	CL_Vec2f screensize1;
	CL_Vec2f screensize2;
	CL_Vec2f screensize3;
	float v7, v10, v24, v14, v15;
	int v16;
	float v11;
	int x;
	int v9;
	int y;
	int v13;
	int v17;
	
	int v23;
	unsigned int first_part_of_a_float;
	Surface* v18;
	
	
	CL_Vec2f v20;
	CL_Vec2f v19;
	screensize1 = GetScreenSize();
	x = screensize1.x;
	screensize2 = GetScreenSize();
	y = screensize2.y; //v8
	v7 = (float)(x * 0.0019531) * 512.0;
	v9 = floorf((float)(a3->x) * (float)((float)(hillnumbers + 1) * 0.2) * m_Scale_X);
	v23 = v9;
	v10 = v7 + v9;
	v24 = v10;
	screensize3 = GetScreenSize();
	
	if (v10 < 0.0)
	{
		do
		{
			v11 = v10;
			v10 = v7 + v10;
		} while (v10 < 0.0);
		v23 = v11;
	}
	if (!hillnumbers)
		first_part_of_a_float = 0xC2000000;
	v24 = (float)((float)(y + 2.0) - (float)((float)(x * 0.0019531) * (float)(22 * (2 - hillnumbers)))) + 1.0;
	switch (hillnumbers) {
	case 0:
		v13 = -46;
		v14 = x * 0.0019531;

	LABEL_13:
		v24 = (float)(y + 2.0) + (float)(v14 * v13);
		break;
	case 1:
		v14 = x * 0.0019531;
		v13 = 60.0;
		goto LABEL_13;
	case 2:
		v24 = y + 2.0;
		break;
	}
	v15 = v23;
	if (v23 <= x) {
		v16 = hillnumbers;
		v17 = v24;
		do
		{
			v18 = &this->m_hills[v16];
			v19.x = x * 0.0019531;
			v19.y = x * 0.0019531;
			v18->BlitScaled(v15, v17, v19, ALIGNMENT_UPPER_LEFT, -1, 0, 0);
			v15 = v15 + v7;
		} while (x >= v15);
	}
}
void Background::SortClouds() {
	unsigned int nCloudsMinus1; // r6
	int v2; // r4
	int bChangedAnything; // r11
	unsigned int i; // r5
	Cloud* v5; // r10
	Cloud* v6; // r7
	Cloud* v7; // r10
	float v8; // r1
	int v9; // r2
	int v10; // r3
	float* v11; // r7
	int v12; // r1
	int v13; // r2
	float* v14; // r10
	Cloud v15; // [sp+14h] [bp-44h]
	nCloudsMinus1 = m_num_clouds - 1;         // this is literally bubble sort
	do {
		v2 = 0;
		bChangedAnything = 1;
		i = 0;
		while (i < nCloudsMinus1) {
			v5 = m_clouds;
			++i;
			v6 = &v5[v2++];
			v7 = &v5[v2];
			if (v6->field_10 > v7->field_10) {
				std::swap(*v6, *v7);
				bChangedAnything = 0;
			}

		}
		
	}
	while (!bChangedAnything);
}
