#include "VanillaStyle/Helper/ProgressBarStyle.h"
#include <QPainter>
#include <QSvgRenderer>

namespace VanillaStyle
{
void ProgressBarStyle::drawGroove(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        // auto radius = theme->getRadius(Theme::ButtonRadius);
        painter->setRenderHint(QPainter::Antialiasing);
        // buttonOutlineColor
        // painter->setPen(QColor(198, 220, 186));
        // baseBackground
        const QColor bgColor = theme->getColor(option, Theme::ProgressBarBackground);
        painter->setPen(QPen(bgColor, 2, Qt::DashLine));

        const auto rect = progressBarOption->rect;
        painter->drawLine(QPoint(rect.right(), rect.height() / 2), QPoint(rect.left(), rect.height() / 2));
        painter->setBrush(QBrush(bgColor));
        // const qreal radius = option->rect.height() / 2;

        // painter->drawRoundedRect(QRectF(progressBarOption->rect), radius, radius);
    }
}
void ProgressBarStyle::drawContents(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    Q_UNUSED(widget);
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        const auto value = progressBarOption->progress - progressBarOption->minimum;
        const auto range = progressBarOption->maximum - progressBarOption->minimum;
        if (value > 0)
        {
            painter->setRenderHint(QPainter::Antialiasing);
            const auto rect = progressBarOption->rect;

            const QColor fgColor = theme->getColor(option, Theme::ProgressBarForeground);
            painter->setPen(QPen(fgColor, 2, Qt::SolidLine));

            const auto percentage = 1 - static_cast<double>(value) / static_cast<double>(range);
            const auto progressRect = rect.adjusted(0, 0, -static_cast<int>(rect.width() * percentage), 0);
            painter->drawLine(QPoint(progressRect.right(), progressRect.height() / 2), QPoint(progressRect.left(), progressRect.height() / 2));

            const auto planeRect = QRect(progressRect.right(), progressRect.top(), progressRect.height(), progressRect.height());
            const auto path = theme->getIconPath(Theme::IconRole::ProgressIndicator);
            // const auto path = QStringLiteral(":VanillaStyle/icons/Airplane.svg");
            if (path.isEmpty())
            {
                return;
            }
            renderSvgFromPath(path, painter, planeRect);
            // render.render(painter, planeRect);
            // const QRect usableRect = progressBarOption->rect.adjusted(3, 3, -3, -3);
            // QRect progressRect = usableRect;
            // progressRect.setWidth(double(value) / double(range) * usableRect.width());
            //
            // // progressBarOutlineBrush
            // painter->setPen(Qt::NoPen);
            // // progressBarContentsBrush
            // const QColor fgColor = theme->getColor(option, Theme::ProgressBarForeground);
            // painter->setBrush(fgColor);
            // const qreal radius = progressBarOption->rect.height() / 2 - 2.5;
            // painter->drawRoundedRect(QRectF(progressRect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);

            // QRect repaintedGrooveRect = option->rect;
            // repaintedGrooveRect.setWidth(double(value) / double(range) * repaintedGrooveRect.width());
            // painter->setClipRect(repaintedGrooveRect);
            // painter->setPen(QPen(QColor(198, 210, 156)));
            // painter->setBrush(Qt::NoBrush);
            // painter->setOpacity(0.43);
            // painter->drawRoundedRect(QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5), radius, radius);
        }
    }
}
void ProgressBarStyle::drawText(const QStyleOption* option, QPainter* painter, const QWidget* widget, const Theme* theme)
{
    Q_UNUSED(widget)
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        const QPen oldPen = painter->pen();
        // progressBarTextColor
        const QColor tColor = theme->getColor(option, Theme::ProgressBarText);
        painter->setPen(tColor);
        const auto textRext = progressBarOption->rect.adjusted(0, 0, 0, -progressBarOption->rect.height() / 2 - 2);
        painter->drawText(textRext, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, progressBarOption->text);
        painter->setPen(oldPen);
    }
}
QRect ProgressBarStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget)
{
    Q_UNUSED(widget)
    if (const auto* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option))
    {
        if (subElement == QStyle::SE_ProgressBarLabel)
        {
            return progressBarOption->rect.adjusted(0, 0, -6, 0);  // right-align before the round rect
        }
        // The area for both groove and content is the whole rect. The drawing will take care of actual contents rect.
        return progressBarOption->rect;
    }
    return option->rect;
}
}  // namespace VanillaStyle