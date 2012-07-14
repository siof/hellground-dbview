/*
*    Copyright (C) 2012 lukaasm <lukaasm.pl>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Affero General Public License version 3 as
*    published by the Free Software Foundation.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MainSite.h"

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WString>

#include "Language.h"
#include "LoginWidget.h"
#include "SearchWidget.h"

#include <Wt/Dbo/backend/MySQL.h>

int main(int argc, char* argv[])
{
    return Wt::WRun(argc, argv, &MainSite::Create);
}

Wt::WApplication* MainSite::Create(const Wt::WEnvironment& e)
{
    return new MainSite(e);
}

void MainSite::CreateLoginDialog()
{
    LoginWidget::Create()->show();
}

MainSite::MainSite(const Wt::WEnvironment& e) : Wt::WApplication(e)
{
    messageResourceBundle().use("res/lang/general");
    useStyleSheet("res/style.css");

    setTitle(Wt::WWidget::LANG_SITE_TITLE);

    Wt::Dbo::backend::MySQL session("world", "root", "root");
    Wt::WContainerWidget* header = new Wt::WContainerWidget(root());
    header->setId("header");
    header->setContentAlignment(Wt::AlignRight);

    Wt::WPushButton* b = new Wt::WPushButton(Wt::WWidget::LANG_SIGNIN, header);
    b->setStyleClass("header");
    b->clicked().connect(SLOT(this, MainSite::CreateLoginDialog));

    b = new Wt::WPushButton(Wt::WWidget::LANG_REGISTER, header);
    b->setStyleClass("header");

    root()->addWidget(new SearchWidget());

    Wt::WStackedWidget* body = new Wt::WStackedWidget(root());
    body->setId("content");
}
