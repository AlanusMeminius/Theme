#include <QFileInfo>
#include <QToolTip>
#include <QPainter>

#include "VanillaStyle/Theme/Theme.h"
#include "VanillaStyle/Theme/Config.h"
#include "VanillaStyle/Theme/ConfigManager.h"

namespace Vanilla
{
Theme::State Theme::state(const QStyleOption* option)
{
    State state = Normal;
    if (!option->state.testFlag(QStyle::State_Enabled))
    {
        return Disabled;
    }
    if (option->state.testFlag(QStyle::State_MouseOver))
    {
        state = Hover;
    }
    if (option->state.testFlag(QStyle::State_Sunken))
    {
        state = Press;
    }
    return state;
}

Theme::StateFlags Theme::flags(const QStyleOption* option)
{
    StateFlags flags{0};

    if (option->state.testFlag(QStyle::State_On))
    {
        flags |= Checked;
    }

    if (option->state.testFlag(QStyle::State_Selected))
    {
        flags |= Selected;
    }

    if (option->state.testFlag(QStyle::State_HasFocus))
    {
        flags |= Focus;
    }
    return flags;
}

Theme::Theme()
    : configManager(std::make_shared<ConfigManager>())
{
    styleConfig = configManager->defaultConfig();
    initPalette();
}

void Theme::setConfig(const std::string& configPath)
{
    styleConfig = std::move(configManager->getConfig(configPath));
    auto callback = [this](const ConfigErrorHanler::ErrorCode& error) {
        if (error != ConfigErrorHanler::ErrorCode::NoError)
        {
        }
    };
    configManager->setErrorHandler(callback);
}

void Theme::initPalette()
{
    palette.setColor(QPalette::Window, Qt::transparent);
    palette.setColor(QPalette::Base, styleConfig.color.backgroundColor);
    palette.setColor(QPalette::WindowText, styleConfig.color.primaryColor);
    palette.setColor(QPalette::Text, styleConfig.color.primaryColor);
    palette.setColor(QPalette::Highlight, QColor(0x53, 0x94, 0x9f));

    // Text color on buttons
    palette.setColor(QPalette::ButtonText, styleConfig.color.primaryColor);

    // pal.setColor(QPalette::ToolTipBase, baseBackground());
    palette.setColor(QPalette::ToolTipText, styleConfig.color.primaryColor);

    QToolTip::setPalette(palette);
}

QPalette Theme::standardPalette() const
{
    return palette;
}

int Theme::getRadius(const RadiusRole radiusRole) const
{
    switch (radiusRole)
    {
    case ButtonRadius:
        return 4;
    case ProgressRadius:
        return 3;
    default:
        return 5;
    }
}

int Theme::getSize(const SizeRole sizeRole) const
{
    switch (sizeRole)
    {
    case ButtonBorder:
        return 1;
    case CheckBoxBorder:
        return 2;
    case MenuItemPadding:
        return 5;
    case IconSize:
        return styleConfig.size.iconSize;
    case CheckBoxIndicatorMargin:
        return 4;
    case CheckBoxSpacing:
        return 5;
    case ProgressBarHeight:
        return 6;
    case ProgressBarTextMargin:
        return 35;
    default:
        return 3;
    }
}

QFont Theme::getFont(const TextSizeRole sizeRole)
{
    QFont font;
    font.setWeight(QFont::Weight::Normal);
    font.setPixelSize(16);
    switch (sizeRole)
    {
    case H6:
        font.setPixelSize(11);
        break;
    case H5:
        font.setPixelSize(13);
        break;
    case H4:
        font.setPixelSize(16);
        break;
    case H3:
        font.setPixelSize(19);
        break;
    case H2:
        font.setPixelSize(24);
        break;
    case H1:
        font.setPixelSize(32);
    default:
        break;
    }
    return font;
}

QColor Theme::getColor(const QStyleOption* option, const ColorRole role) const
{
    return createColor(state(option), option, role);
}

QColor Theme::createColor(const State state, const QStyleOption* option, const ColorRole role) const
{
    return createColor(flags(option) | state, option, role);
}

QColor Theme::createColor(StateFlags flags, const QStyleOption* option, ColorRole role) const
{
    QColor color = option->palette.color(QPalette::Base);
    switch (role)
    {
    case PrimaryText:
    {
        color = styleConfig.color.primaryColor;
        break;
    }
    case LabelText:
    {
        if ((flags & Flag) == Disabled)
        {
            color = QColor(Qt::gray);
        }
        else if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.hoverTextColor;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.pressedTextColor;
        }
        else
        {
            color = styleConfig.color.textColor;
        }
        break;
    }
    case ButtonForeground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.buttonHoveredForeground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.buttonPressedForeground;
        }
        else
        {
            color = styleConfig.color.buttonForeground;
        }
        break;
    }
    case ButtonBackground:
    {
        if ((flags & Flag) == Hover)
        {
            color = styleConfig.color.buttonHoveredBackground;
        }
        else if ((flags & Flag) == Press)
        {
            color = styleConfig.color.buttonPressedBackground;
        }
        else
        {
            color = styleConfig.color.buttonBackground;
        }
        break;
    }
    case ButtonBorderColor:
    {
        color = styleConfig.color.buttonBorderColor;
        break;
    }
    case RadioButtonForeground:
    {
        // color = QColor(253, 164, 3);
        color = styleConfig.color.checkBoxForeground;
        break;
    }
    case CheckBoxForeground:
    {
        color = styleConfig.color.checkBoxCheckedForeground;
        break;
    }
    case RadioButtonBackground:
    {
        if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = styleConfig.color.checkBoxCheckedBackground;
        }
        else
        {
            color = styleConfig.color.checkBoxBackground;
        }
        break;
    }
    case CheckBoxBackground:
    {
        if ((flags & Checked) == Checked)
        {
            color = styleConfig.color.checkBoxCheckedBackground;
        }
        else if ((flags & Checked) != Checked && (flags & Flag) == Hover)
        {
            color = styleConfig.color.checkBoxHoveredBackground;
        }
        else
        {
            color = styleConfig.color.checkBoxBackground;
        }
        break;
    }
    case CheckBoxBorderColor:
    {
        color = styleConfig.color.CheckBoxBorderColor;
        break;
    }
    case ProgressBarForeground:
    {
        color = styleConfig.color.progressBarForeground;
        break;
    }
    case ProgressBarBackground:
    {
        color = styleConfig.color.progressBarBackground;
        break;
    }
    case ProgressBarText:
    {
        color = styleConfig.color.progressBarText;
        break;
    }
    case LineEditOutline:
    {
        if ((flags & Flag) == Focus)
        {
            color = styleConfig.color.lineEditFocusOutline;
        }
        else
        {
            color = styleConfig.color.lineEditOutline;
        }
        break;
    }
    default:
        break;
    }
    return color;
}

QColor Theme::customColor(const ColorRole role) const
{
    switch (role)
    {
    case PrimaryText:
    {
        return styleConfig.color.textColor;
    }
    case ButtonForeground:
        return styleConfig.color.buttonForeground;
    case ButtonBackground:
        return styleConfig.color.buttonBackground;
    case LabelText:
        return styleConfig.color.iconLabelText;
    case ToggleButtonBackground:
        return styleConfig.color.toggleButtonBackground;
    case ToggleButtonForeground:
        return styleConfig.color.toggleButtonForeground;
    case ToggleButtonIndicatorColor:
        return styleConfig.color.toggleButtonIndicatorColor;
    default:
        return Qt::white;
    }
}

QString Theme::checkIconFile(const std::string& path) const
{
    if (const QFileInfo file(QString::fromStdString(path)); file.exists())
    {
        return QString::fromStdString(path);
    }
    return {};
}

QString Theme::getIconPath(const IconRole role) const
{
    switch (role)
    {
    case UpArrow:
    {
        return checkIconFile(styleConfig.icons.upArrow);
    }
    case DownArrow:
    {
        return checkIconFile(styleConfig.icons.downArrow);
    }
    case ProgressIndicator:
    {
        return checkIconFile(styleConfig.icons.progressIndicator);
    }
    default:
        return {};
    }
}
Theme::ProgressMode Theme::getProgressMode() const
{
    return ModeOne;
    // return styleConfig.progressBarMode == "mode1" ? ModeOne : ModeTwo;
}
}  // namespace Vanilla