#pragma once

#include <memory>

#include <QRect>
#include <QColor>

class QStyleOption;
class QPainter;
class QWidget;
class QMenu;

namespace Vanilla
{
class Theme;
class MenuStyle
{
public:
    bool drawPrimitive(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    bool drawMenuBarItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    bool drawMenuItem(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget = nullptr) const;
    void drawMenuSeparator(QPainter* painter, const QRect& rect, QColor const& color, int thickness) const;
    void eventFilter(QMenu* obj) const;
};

}  // namespace VanillaStyle