target triple = "x86_64-pc-linux-gnu"


@format.pint = constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8* %format, ...)

define void @print_int(i32 %x) {
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8],[4 x i8]* @format.pint, i64 0, i64 0), i32 %x)
  ret void
}

define i32 @main() #0{
  %t1 = alloca i32, align 4
  %t2 = alloca i32, align 4
  store i32 0, i32* %t2
  %t3 = load i32, i32* %t2
  store i32 %t3, i32* %t1
  %t4 = alloca i32, align 4
  %t5 = alloca i32, align 4
  store i32 5, i32* %t5
  %t6 = load i32, i32* %t5
  store i32 %t6, i32* %t4
  %t7 = alloca i32, align 4
  %t8 = alloca i32, align 4
  store i32 0, i32* %t8
  %t9 = load i32, i32* %t8
  store i32 %t9, i32* %t7
  br label %t10

t10:
  %t13 = alloca i32, align 4
  store i32 5, i32* %t13
  %t14 = load i32, i32* %t13
  %t15 = load i32, i32* %t7
  %t16 = icmp slt i32 %t15, %t14
  br i1 %t16, label %t11, label %t12

t11:
  %t17 = load i32, i32* %t4
  %t18 = load i32, i32* %t1
  %t19 = add nsw i32 %t18, %t17
  store i32 %t19, i32* %t1
  %t20 = alloca i32, align 4
  store i32 1, i32* %t20
  %t21 = load i32, i32* %t20
  %t22 = load i32, i32* %t7
  %t23 = add nsw i32 %t22, %t21
  store i32 %t23, i32* %t7
  br label %t10

t12:
  %t24 = load i32, i32* %t1
  call void @print_int(i32 %t24)
  ret i32 0
}

attributes #0 = { "frame-pointer"="all" }
