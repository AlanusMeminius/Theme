#pragma once
#include <QApplication>
#include <QSettings>
#include <QColor>

#include <nlohmann/json.hpp>

namespace nlohmann
{
template <>
struct adl_serializer<QColor>
{
    static void to_json(nlohmann::json& j, const QColor& color)
    {
        try
        {
            j = color.name(QColor::HexArgb).toStdString();
        }
        catch (const std::exception& e)
        {
            j = "Error: Unable to convert QColor to hex string";
        }
    }

    static void from_json(const nlohmann::json& j, QColor& color)
    {
        try
        {
            QString colorString = QString::fromStdString(j.get<std::string>());
            if (colorString.startsWith("#"))
            {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                color = QColor::fromString(colorString);
#else
                color = QColor();
                color.setNamedColor(colorString);
#endif
            }
        }
        catch (const std::exception& e)
        {
            color = QColor(Qt::black);
        }
    }
};
}  // namespace nlohmann

namespace Vanilla
{

class Basic
{
public:
    Basic() = default;
    virtual ~Basic() = default;
    virtual std::string toString() = 0;
};

class Color : public Basic
{
public:
    QColor backgroundColor;
    QColor primaryColor;
    QColor textColor;
    QColor pressedTextColor;
    QColor hoverTextColor;
    QColor buttonForeground;
    QColor buttonHoveredForeground;
    QColor buttonPressedForeground;
    QColor buttonBackground;
    QColor buttonHoveredBackground;
    QColor buttonPressedBackground;
    QColor buttonBorderColor;
    QColor checkBoxBackground;
    QColor checkBoxForeground;
    QColor checkBoxCheckedForeground;
    QColor checkBoxCheckedBackground;
    QColor checkBoxHoveredBackground;
    QColor CheckBoxBorderColor;
    QColor progressBarBackground;
    QColor progressBarForeground;
    QColor progressBarText;
    QColor toggleButtonBackground;
    QColor toggleButtonForeground;
    QColor toggleButtonIndicatorColor;
    QColor lineEditFocusOutline;
    QColor lineEditOutline;
    QColor iconLabelText;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Color, backgroundColor, primaryColor, textColor, pressedTextColor, hoverTextColor, buttonForeground,
                                                buttonBackground, buttonHoveredForeground, buttonPressedForeground, buttonHoveredBackground,
                                                buttonPressedBackground, buttonBorderColor, checkBoxBackground, checkBoxForeground, checkBoxCheckedBackground,
                                                checkBoxCheckedForeground, checkBoxHoveredBackground, CheckBoxBorderColor, progressBarBackground,
                                                progressBarForeground, progressBarText, toggleButtonBackground,toggleButtonForeground,toggleButtonIndicatorColor,lineEditFocusOutline, lineEditOutline, iconLabelText);
};

class Size : public Basic
{
public:
    int fontSize{};
    int borderWidth{};
    int iconSize{};
    int normalRadius{};
    int buttonRadius{};
    int menuItemRadius{};
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Size, fontSize, borderWidth, iconSize, normalRadius, buttonRadius);
};

class Icons : public Basic
{
public:
    std::string upArrow;
    std::string downArrow;
    std::string progressIndicator;
    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Icons, upArrow, downArrow, progressIndicator);
};

class StyleConfig : public Basic
{
public:
    std::string name;
    std::string author;
    std::string mode;
    Color color;
    Size size;
    Icons icons;

    std::string toString()
    {
        nlohmann::json json;
        to_json(json, *this);
        return json.dump(4);
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(StyleConfig, name, author, mode, color, size, icons);
};

}  // namespace Vanilla
