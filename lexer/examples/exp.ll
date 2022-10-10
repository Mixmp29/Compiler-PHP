target triple = "x86_64-pc-linux-gnu"

@str29 = constant [9 x i8] c"Result: \00"

@format.str = constant [4 x i8] c"%s\0A\00"

@format.pint = constant [4 x i8] c"%d\0A\00"

@format.rint = constant [3 x i8] c"%d\00"

declare i32 @printf(i8* %format, ...)

declare i32 @__isoc99_scanf(i8*, ...)

define void @print_int(i32 %x) {
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8],[4 x i8]* @format.pint, i64 0, i64 0), i32 %x)
  ret void
}

define void @print_string(i8* %x) {
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @format.str, i64 0, i64 0), i8* %x)
  ret void
}

define void @read_int(i32* %x) {
  call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr ([3 x i8], [3 x i8]* @format.rint, i64 0, i64 0), i32* %x)
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
  store i32 1, i32* %t5
  %t6 = load i32, i32* %t5
  store i32 %t6, i32* %t4
  %t7 = alloca i32, align 4
  %t8 = alloca i32, align 4
  store i32 0, i32* %t8
  %t9 = load i32, i32* %t8
  store i32 %t9, i32* %t7
  %t10 = alloca i32, align 4
  %t11 = alloca i32, align 4
  call void @read_int(i32* %t11)
  %t12 = load i32, i32* %t11
  store i32 %t12, i32* %t10
  br label %t13

t13:
  %t16 = load i32, i32* %t10
  %t17 = load i32, i32* %t7
  %t18 = icmp slt i32 %t17, %t16
  br i1 %t18, label %t14, label %t15

t14:
  %t19 = load i32, i32* %t4
  %t20 = load i32, i32* %t1
  %t21 = add nsw i32 %t20, %t19
  store i32 %t21, i32* %t1
  %t22 = load i32, i32* %t4
  %t23 = load i32, i32* %t1
  %t24 = sub nsw i32 %t23, %t22
  store i32 %t24, i32* %t4
  %t25 = alloca i32, align 4
  store i32 1, i32* %t25
  %t26 = load i32, i32* %t25
  %t27 = load i32, i32* %t7
  %t28 = add nsw i32 %t27, %t26
  store i32 %t28, i32* %t7
  br label %t13

t15:
  %t29 = getelementptr inbounds [9 x i8], [9 x i8]* @str29, i64 0, i64 0
  call void @print_string(i8* %t29)
  %t30 = load i32, i32* %t1
  call void @print_int(i32 %t30)
  ret i32 0
}

attributes #0 = { "frame-pointer"="all" }
