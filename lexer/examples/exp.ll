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
  store i32 10000, i32* %t2
  %t3 = load i32, i32* %t2
  store i32 %t3, i32* %t1
  %t4 = alloca i32, align 4
  %t5 = alloca i32, align 4
  store i32 15, i32* %t5
  %t6 = load i32, i32* %t5
  store i32 %t6, i32* %t4
  %t7 = alloca i32, align 4
  %t8 = alloca i32, align 4
  store i32 21, i32* %t8
  %t9 = load i32, i32* %t8
  store i32 %t9, i32* %t7
  %t10 = alloca i32, align 4
  %t11 = alloca i32, align 4
  store i32 0, i32* %t11
  %t12 = load i32, i32* %t11
  store i32 %t12, i32* %t10
  %t13 = load i32, i32* %t7
  %t14 = load i32, i32* %t4
  %t15 = icmp slt i32 %t14, %t13
  br i1 %t15, label %t16, label %t17

t16:
  br label %t19

t19:
  %t22 = alloca i32, align 4
  store i32 3, i32* %t22
  %t23 = load i32, i32* %t22
  %t24 = load i32, i32* %t10
  %t25 = icmp slt i32 %t24, %t23
  br i1 %t25, label %t20, label %t21

t20:
  %t26 = load i32, i32* %t7
  call void @print_int(i32 %t26)
  %t27 = alloca i32, align 4
  store i32 8, i32* %t27
  %t28 = load i32, i32* %t27
  %t29 = load i32, i32* %t7
  %t30 = add nsw i32 %t29, %t28
  store i32 %t30, i32* %t7
  %t31 = alloca i32, align 4
  %t32 = load i32, i32* %t31
  %t33 = load i32, i32* %t7
  %t34 = add nsw i32 %t33, %t32
  store i32 %t34, i32* %t7
  %t35 = alloca i32, align 4
  store i32 1, i32* %t35
  %t36 = load i32, i32* %t35
  %t37 = load i32, i32* %t10
  %t38 = add nsw i32 %t37, %t36
  store i32 %t38, i32* %t10
  %t39 = load i32, i32* %t10
  call void @print_int(i32 %t39)
  %t40 = load i32, i32* %t7
  call void @print_int(i32 %t40)
  br label %t19

t21:
  %t41 = load i32, i32* %t31
  %t42 = load i32, i32* %t7
  %t43 = add nsw i32 %t42, %t41
  store i32 %t43, i32* %t7
  br label %t18

t17:
  %t44 = load i32, i32* %t7
  %t45 = load i32, i32* %t4
  %t46 = add nsw i32 %t45, %t44
  store i32 %t46, i32* %t4
  %t47 = alloca i32, align 4
  store i32 1, i32* %t47
  %t48 = load i32, i32* %t47
  %t49 = load i32, i32* %t4
  %t50 = add nsw i32 %t49, %t48
  store i32 %t50, i32* %t4
  br label %t18

t18:
  %t51 = alloca i32, align 4
  store i32 15, i32* %t51
  %t52 = load i32, i32* %t51
  %t53 = load i32, i32* %t7
  %t54 = add nsw i32 %t53, %t52
  store i32 %t54, i32* %t7
  %t55 = load i32, i32* %t7
  call void @print_int(i32 %t55)
  ret i32 0
}

attributes #0 = { "frame-pointer"="all" }
