/******************************************************************************
 *
 * Copyright (c) 2020 Cogent Embedded Inc. ALL RIGHTS RESERVED.
 *
 * THIS FILE IS SUBJECT TO THE LICENSE TERMS PROVIDED IN THE 'LICENSE' FILE
 * FOUND IN THE TOP-LEVEL DIRECTORY OF THIS SOFTWARE PACKAGE OR BY REQUEST VIA
 * http://cogentembedded.com, source@cogentembedded.com
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/
#include <QAbstractVideoSurface>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVideoSurfaceFormat>
#include <QtQuick/QQuickItem>
#include <gst/gst.h>

#include "v4l2source.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    gst_init(&argc, &argv);
    QGuiApplication app(argc, argv);

    qmlRegisterType<V4L2Source>("v4l2source", 1, 0, "CameraSource");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
