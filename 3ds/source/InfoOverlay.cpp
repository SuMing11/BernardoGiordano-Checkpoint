/*
 *   This file is part of Checkpoint
 *   Copyright (C) 2017-2019 Bernardo Giordano, FlagBrew
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#include "InfoOverlay.hpp"

InfoOverlay::InfoOverlay(Screen& screen, const std::string& mtext) : Overlay(screen)
{
    textBuf = C2D_TextBufNew(64);
    button  = std::make_unique<Clickable>(42, 162, 236, 36, COLOR_GREY_DARK, COLOR_WHITE, "OK", true);
    button->selected(true);
    std::string t = StringUtils::wrap(mtext, size, 220);
    C2D_TextParse(&text, textBuf, t.c_str());
    C2D_TextOptimize(&text);
    posx = ceilf(320 - StringUtils::textWidth(text, size)) / 2;
    posy = 40 + ceilf(120 - StringUtils::textHeight(t, size)) / 2;
}

InfoOverlay::~InfoOverlay(void)
{
    C2D_TextBufDelete(textBuf);
}

void InfoOverlay::drawTop(void) const
{
    C2D_DrawRectSolid(0, 0, 0.5f, 400, 240, COLOR_OVERLAY);
}

void InfoOverlay::drawBottom(void) const
{
    C2D_DrawRectSolid(0, 0, 0.5f, 320, 240, COLOR_OVERLAY);
    C2D_DrawRectSolid(40, 40, 0.5f, 240, 160, COLOR_GREY_DARK);
    C2D_DrawText(&text, C2D_WithColor, posx, posy, 0.5f, size, size, COLOR_WHITE);
    button->draw(0.7f, COLOR_BLUE);
    Gui::drawPulsingOutline(42, 162, 236, 36, 2, COLOR_BLUE);
}

void InfoOverlay::update(InputState* touch)
{
    if (button->released() || (hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_B)) {
        screen.removeOverlay();
    }
}