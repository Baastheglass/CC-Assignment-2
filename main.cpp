#include <llvm-19/llvm/IR/LLVMContext.h>
#include <llvm-19/llvm/IR/IRBuilder.h>
#include <llvm-19/llvm/IR/Module.h>
#include <llvm-19/llvm/IR/Function.h>
#include <llvm-19/llvm/Support/raw_ostream.h>

using namespace llvm;

int main() {
    //creating LLVM context and module within which code will exist
    LLVMContext context; 
    std::unique_ptr<Module> module = std::make_unique<Module>("module_name", context);
    IRBuilder<> builder(context);
    
    //creating an Int type for further use
    Type *intTy = builder.getInt32Ty();

    //arithmetic function
    std::vector<Type *> arithmeticParams = {intTy, intTy};
    FunctionType *arithmeticTy = FunctionType::get(builder.getVoidTy(), arithmeticParams, false);
    Function *arithmeticFunction = Function::Create(arithmeticTy, Function::InternalLinkage, "arithmetic", *module);

    //arithmetic function body and creating its arguments and iterator for iterating through them
    Function::arg_iterator args = arithmeticFunction->arg_begin();
    Value *arg1 = &*args++;
    arg1->setName("arg1");
    Value *arg2 = &*args++;
    arg2->setName("arg2");

    //actual arithmetic function functionality defined here
    BasicBlock *entry = BasicBlock::Create(context, "entry-block", arithmeticFunction);
    builder.SetInsertPoint(entry);

    Value *add = builder.CreateAdd(arg1, arg2);
    Value *subtract = builder.CreateSub(arg1, arg2);
    Value *multiply = builder.CreateMul(arg1, arg2);
    Value *divide = builder.CreateSDiv(arg1, arg2);

    //initialising print Functionality
    module->setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
    std::vector<Type *> printfParams = {builder.getPtrTy()};
    FunctionType *printfTy = FunctionType::get(builder.getInt32Ty(), printfParams, true);
    Function *printfFunc = Function::Create(printfTy, Function::ExternalLinkage, "printf", *module);

    Constant *formatStr = builder.CreateGlobalStringPtr("add: %d, sub: %d, mul: %d, div: %d\n");

    std::vector<Value *> printfArgs = {formatStr, add, subtract, multiply, divide};
    builder.CreateCall(printfFunc, printfArgs);

    builder.CreateRetVoid();

    //main function
    FunctionType *mainTy = FunctionType::get(intTy, false); // Return i32, no parameters
    Function *mainFunction = Function::Create(mainTy, Function::ExternalLinkage, "main", *module);

    BasicBlock *mainEntry = BasicBlock::Create(context, "main-entry", mainFunction);
    builder.SetInsertPoint(mainEntry);
    //running Hello world using the print function
    Constant *helloString = builder.CreateGlobalStringPtr("Hello, World!\n");
    std::vector<Value *> printfArgs2 = {helloString};
    builder.CreateCall(printfFunc, printfArgs2);

    //call arithmetic with constant values
    std::vector<Value *> arithmeticArgs = {ConstantInt::get(intTy, 10), ConstantInt::get(intTy, 5)};
    builder.CreateCall(arithmeticFunction, arithmeticArgs);

    builder.CreateRet(ConstantInt::get(intTy, 0)); // Return 0

    module->print(outs(), nullptr);
    return 0;
}