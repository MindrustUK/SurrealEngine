
#include "Precomp.h"
#include "Editor3DViewport.h"
#include "Engine.h"
#include "Render/RenderSubsystem.h"
#include "UI/Core/Colorf.h"

Editor3DViewport::Editor3DViewport(Widget* parent) : EditorViewport(parent)
{
}

Editor3DViewport::~Editor3DViewport()
{
}

void Editor3DViewport::OnPaint(Canvas* canvas)
{
	canvas->fillRect(Rect::xywh(0.0, 0.0, GetWidth(), GetHeight()), Colorf(40 / 255.0f, 40 / 255.0f, 40 / 255.0f));

	if (!engine)
		return;

	Point topLeft = MapTo(Window(), Point(0.0, 0.0));

	canvas->begin3d();

	if (!engine->render)
		engine->render = std::make_unique<RenderSubsystem>(Window()->GetRenderDevice());

	engine->CameraLocation = Location;
	engine->CameraRotation = Rotation;
	engine->ViewportX = (int)std::round(topLeft.x);
	engine->ViewportY = (int)std::round(topLeft.y);
	engine->ViewportWidth = (int)std::round(GetWidth());
	engine->ViewportHeight = (int)std::round(GetHeight());
	engine->render->DrawEditorViewport();

	canvas->end3d();
}

void Editor3DViewport::OnMouseMove(const Point& pos)
{
}

void Editor3DViewport::OnMouseDown(const Point& pos, int key)
{
	SetFocus();
	if (key == IK_RightMouse)
	{
		LockCursor();
		MouseIsPanning = true;
	}
	else if (key == IK_MiddleMouse)
	{
		LockCursor();
		MouseIsMoving = true;
	}
}

void Editor3DViewport::OnMouseDoubleclick(const Point& pos, int key)
{
}

void Editor3DViewport::OnMouseUp(const Point& pos, int key)
{
	if (key == IK_RightMouse && MouseIsPanning)
	{
		UnlockCursor();
		MouseIsPanning = false;
	}
	else if (key == IK_MiddleMouse && MouseIsMoving)
	{
		UnlockCursor();
		MouseIsMoving = false;
	}
}

void Editor3DViewport::OnKeyDown(EInputKey key)
{
	if (key == IK_W)
	{
		MoveCamera(0.0f, 0.0f, 100.0f);
	}
	else if (key == IK_S)
	{
		MoveCamera(0.0f, 0.0f, -100.0f);
	}
	else if (key == IK_A)
	{
		MoveCamera(0.0f, -100.0f, 0.0f);
	}
	else if (key == IK_D)
	{
		MoveCamera(0.0f, 100.0f, 0.0f);
	}
}

void Editor3DViewport::OnKeyUp(EInputKey key)
{
}

void Editor3DViewport::OnRawMouseMove(int dx, int dy)
{
	if (MouseIsPanning)
	{
		Rotation.Yaw += dx * 10;
		Rotation.Pitch = clamp(Rotation.Pitch + dy * 10, -90 * 65536 / 360, 90 * 65536 / 360);
		Update();
	}
	else if (MouseIsMoving)
	{
		MoveCamera((float)-dy, (float)dx, 0.0f);
	}
}

void Editor3DViewport::MoveCamera(float x, float y, float z)
{
	vec3 axisX, axisY, axisZ;
	Coords::Rotation(Rotation).GetAxes(axisX, axisY, axisZ);
	Location += axisX * x;
	Location += axisY * y;
	Location += axisZ * z;
	Update();
}
