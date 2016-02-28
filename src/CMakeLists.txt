set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(MOC_HDRS
    Path2dView.hpp
    Path2dViewPlugin.hpp
)

SET(HDRS
    Path2dView.hpp
)

FILE(GLOB SRCS
    *.cpp
)

FILE(GLOB UI_FILES
    *.ui
)

SET(QtApp_RCCS resources.qrc)

rock_vizkit_widget(Path2dView
    SOURCES ${SRCS} ${QtApp_RCC_SRCS}
    HEADERS ${HDRS}
    MOC ${MOC_HDRS}
    DEPS_PKGCONFIG base-types QtCore QtGui
    UI ${UI_FILES}
)

QT4_ADD_RESOURCES(QtApp_RCC_SRCS ${QtApp_RCCS})

