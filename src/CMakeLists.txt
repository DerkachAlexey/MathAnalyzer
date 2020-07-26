
set(SRC 

    Core/Diff.h
    Core/Diff.cpp
    Core/Simplifier.cpp
    Core/Simplifier.h
    Core/Utils.cpp
    Core/Utils.h
    Core/Parser.cpp
    Core/Parser.h
    Core/Computer.cpp
    Core/Computer.h
    Core/Function.h
    Core/Function.cpp
    Core/MathVector.h
    Core/MathVector.cpp
    Core/MathUtils.h
    Core/MathUtils.cpp
    Core/MathMatrix.h
    Core/MathMAtrix.cpp
    
    Nodes/AdditionExpression.h
    Nodes/AdditionExpression.cpp
    Nodes/Constant.h
    Nodes/Constant.cpp
    Nodes/DifferenceExpression.h
    Nodes/DifferenceExpression.cpp
    Nodes/DivideExpression.h
    Nodes/DivideExpression.cpp
    Nodes/Expression.h
    Nodes/Expression.cpp
    Nodes/PowerExpression.h
    Nodes/PowerExpression.cpp
    Nodes/PrimitiveSymbol.h
    Nodes/PrimitiveSymbol.cpp
    Nodes/ProductExpression.h
    Nodes/ProductExpression.cpp
    Nodes/Symbol.h
    Nodes/Symbol.cpp
    Nodes/ArgumentSymbol.h
    Nodes/ArgumentSymbol.cpp
    Nodes/StringConstant.cpp
    Nodes/StringConstant.h

    Nodes/FunctionSymbol.h
    Nodes/FunctionSymbol.cpp
    Nodes/SymbolFactory.h
    Nodes/SymbolFactory.cpp

    Visitors/DiffVisitor.h
    Visitors/DiffVisitor.cpp
    Visitors/SimplifyVisitor.h
    Visitors/SimplifyVisitor.cpp
    Visitors/SymbolVisitor.h
    Visitors/SymbolVisitor.cpp
    Visitors/VisualiserVis.h
    Visitors/VisualiserVis.cpp
    Visitors/ComputeVisitor.h
    Visitors/ComputeVisitor.cpp
    Visitors/ComputeUtils.cpp
    Visitors/ComputeUtils.h
    Visitors/SimplifyUtils.cpp
    Visitors/SimplifyUtils.h
    
    )

add_library(Analyzer ${SRC})

target_include_directories(Analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core ${CMAKE_CURRENT_SOURCE_DIR}/Visitors ${CMAKE_CURRENT_SOURCE_DIR}/Nodes)