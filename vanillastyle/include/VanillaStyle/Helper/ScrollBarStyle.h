#pragma once

#include <QStyleOption>
#include <memory>

class QPainter;
class QStyleOption;
class QWidget;

namespace Vanilla {

class Theme;

class ScrollBarStyle {
public:
    bool drawSlider(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    bool drawAddLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
    bool drawSubLine(const QStyleOption* option, QPainter* painter, const std::shared_ptr<Theme>& theme, const QWidget* widget) const;
};

} // Vanilla