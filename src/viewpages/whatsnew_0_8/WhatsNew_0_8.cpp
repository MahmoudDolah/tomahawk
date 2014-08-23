/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2014, Uwe L. Korn <uwelk@xhochy.com>
 *   Copyright 2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WhatsNew_0_8.h"
#include "ui_WhatsNewWidget_0_8.h"

#include "utils/Logger.h"
#include "utils/ImageRegistry.h"
#include "utils/TomahawkStyle.h"
#include "TomahawkSettings.h"

#include <QLayout>
#include <QScrollArea>
#include <QStackedWidget>

using namespace Tomahawk;
using namespace Tomahawk::Widgets;


WhatsNew_0_8::WhatsNew_0_8( QWidget* parent )
{
    Q_UNUSED( parent );
}


WhatsNew_0_8::~WhatsNew_0_8()
{

}


bool
WhatsNew_0_8::addPageItem() const
{
    return !TomahawkSettings::instance()->value( "whatsnew/deleted-for-0.8", false ).toBool();
}


void
WhatsNew_0_8::onItemDeleted()
{
    TomahawkSettings::instance()->setValue( "whatsnew/deleted-for-0.8", true );
}


WhatsNewWidget_0_8::WhatsNewWidget_0_8( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::WhatsNewWidget_0_8 )
{
    QWidget* widget = new QWidget;
    ui->setupUi( widget );

    {
        QScrollArea* area = new QScrollArea();
        area->setWidgetResizable( true );
        area->setWidget( widget );

        QPalette pal = palette();
        pal.setBrush( backgroundRole(), Qt::white );
        area->setPalette( pal );
        area->setAutoFillBackground( true );
        area->setFrameShape( QFrame::NoFrame );
        area->setAttribute( Qt::WA_MacShowFocusRect, 0 );

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget( area );
        setLayout( layout );
        TomahawkUtils::unmarginLayout( layout );
    }

    int width = ui->widget->minimumSize().width() - ( ui->widget->layout()->contentsMargins().left() + ui->widget->layout()->contentsMargins().right() );
    {
        ui->inboxImage->setPixmap( ui->inboxImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->inboxImage->setFixedHeight( ui->inboxImage->pixmap()->height() );
        ui->inboxButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap inboxPixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/inboxbutton.png", ui->inboxButton->size() );
        ui->inboxButton->setPixmap( inboxPixmap );
        connect( ui->inboxButton, SIGNAL( clicked() ), SLOT( inboxBoxClicked() ) );
    }

    {
        ui->linkImage->setPixmap( ui->linkImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->linkImage->setFixedHeight( ui->linkImage->pixmap()->height() );
        ui->linkButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap pixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/connectivitybutton.png", ui->inboxButton->size() );
        ui->linkButton->setPixmap( pixmap );
        connect( ui->linkButton, SIGNAL( clicked() ), SLOT( urlLookupBoxClicked() ) );
    }

    {
        ui->beatsImage->setPixmap( ui->beatsImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->beatsImage->setFixedHeight( ui->beatsImage->pixmap()->height() );
        ui->beatsButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap beatsPixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/beatsbutton.png", ui->inboxButton->size() );
        ui->beatsButton->setPixmap( beatsPixmap );
        connect( ui->beatsButton, SIGNAL( clicked() ), SLOT( beatsBoxClicked() ) );
    }

    {
        ui->googleImage->setPixmap( ui->googleImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->googleImage->setFixedHeight( ui->googleImage->pixmap()->height() );
        ui->googleButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap pixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/googlebutton.png", ui->inboxButton->size() );
        ui->googleButton->setPixmap( pixmap );
        connect( ui->googleButton, SIGNAL( clicked() ), SLOT( gmusicBoxClicked() ) );
    }

    {
        ui->androidImage->setPixmap( ui->androidImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->androidImage->setFixedHeight( ui->androidImage->pixmap()->height() );
        ui->androidButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap pixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/androidbutton.png", ui->inboxButton->size() );
        ui->androidButton->setPixmap( pixmap );
        connect( ui->androidButton, SIGNAL( clicked() ), SLOT( androidBoxClicked() ) );
    }

    {
        ui->networkImage->setPixmap( ui->networkImage->pixmap()->scaledToWidth( width, Qt::SmoothTransformation ) );
        ui->networkImage->setFixedHeight( ui->networkImage->pixmap()->height() );
        ui->networkButton->setFixedSize( QSize( 80, 80 ) );
        QPixmap networkingPixmap = ImageRegistry::instance()->pixmap( ":/whatsnew_0_8/data/images/networkbutton.png", ui->inboxButton->size() );
        ui->networkButton->setPixmap( networkingPixmap );
        connect( ui->networkButton, SIGNAL( clicked() ), SLOT( networkingBoxClicked() ) );
    }

    {
        QFont font = ui->label->font();
        font.setWeight( QFont::Light );
        font.setPointSize( TomahawkUtils::defaultFontSize() + 38 );
        ui->label->setFont( font );
        ui->label->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 60% ) }" );

        font.setWeight( QFont::Normal );
        font.setPointSize( TomahawkUtils::defaultFontSize() + 1 );
        ui->label_2->setFont( font );
        ui->label_2->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 30% ) }" );

        font.setPointSize( TomahawkUtils::defaultFontSize() + 2 );
        ui->label_3->setFont( font );
        ui->label_3->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
        ui->label_5->setFont( font );
        ui->label_5->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
        ui->label_6->setFont( font );
        ui->label_6->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
        ui->label_7->setFont( font );
        ui->label_7->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
        ui->label_8->setFont( font );
        ui->label_8->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
        ui->label_9->setFont( font );
        ui->label_9->setStyleSheet( "QLabel { color: rgba( 0, 0, 0, 65% ) }" );
    }
}


WhatsNewWidget_0_8::~WhatsNewWidget_0_8()
{
    delete ui;
}


playlistinterface_ptr
WhatsNewWidget_0_8::playlistInterface() const
{
    return playlistinterface_ptr();
}


bool
WhatsNewWidget_0_8::jumpToCurrentTrack()
{
    return false;
}


bool
WhatsNewWidget_0_8::isBeingPlayed() const
{
    return false;
}


void
WhatsNewWidget_0_8::changeEvent( QEvent* e )
{
    QWidget::changeEvent( e );
    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            ui->retranslateUi( this );
            break;

        default:
            break;
    }
}


void
WhatsNewWidget_0_8::inboxBoxClicked()
{
    activateBox( ui->inboxCaption, 0 );
}


void
WhatsNewWidget_0_8::urlLookupBoxClicked()
{
    activateBox( ui->linkCaption, 1 );
}


void
WhatsNewWidget_0_8::beatsBoxClicked()
{
}


void
WhatsNewWidget_0_8::gmusicBoxClicked()
{
}


void
WhatsNewWidget_0_8::networkingBoxClicked()
{
}


void
WhatsNewWidget_0_8::androidBoxClicked()
{
}


void
WhatsNewWidget_0_8::activateBox( QWidget* widget, int activeIndex )
{
    deactivateAllBoxes();

/*    widget->layout()->setContentsMargins( 8, 8, 8, 16 );
    widget->setStyleSheet( activeWidgetThumbStylesheet );

    ui->stackedWidget->setCurrentIndex( activeIndex );*/
}


void
WhatsNewWidget_0_8::deactivateBox( QWidget* widget )
{
/*    widget->layout()->setContentsMargins( 8, 8, 8, 8 );
    widget->setStyleSheet( inactiveWidgetThumbStylesheet );*/
}


void
WhatsNewWidget_0_8::deactivateAllBoxes()
{
/*    deactivateBox( ui->inboxBox );
    deactivateBox( ui->urlLookupBox );
    deactivateBox( ui->trendingBox );
    deactivateBox( ui->beatsBox );
    deactivateBox( ui->gmusicBox );
    deactivateBox( ui->networkingBox );
    deactivateBox( ui->designBox );
    deactivateBox( ui->androidBox );*/
}


Q_EXPORT_PLUGIN2( ViewPagePlugin, WhatsNew_0_8 )
