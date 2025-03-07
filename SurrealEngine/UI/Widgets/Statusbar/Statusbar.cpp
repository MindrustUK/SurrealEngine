
#include "Precomp.h"
#include "Statusbar.h"
#include "UI/Core/Colorf.h"
#include "UI/Widgets/LineEdit/LineEdit.h"

Statusbar::Statusbar(Widget* parent) : Widget(parent)
{
	CommandEdit = new LineEdit(this);
	CommandEdit->SetFrameGeometry(Rect::xywh(90.0, 4.0, 400.0, 23.0));
}

Statusbar::~Statusbar()
{
}

void Statusbar::OnPaint(Canvas* canvas)
{
	canvas->drawText(Point(16.0, 21.0), Colorf(0.0f, 0.0f, 0.0f), "Command:");
}
