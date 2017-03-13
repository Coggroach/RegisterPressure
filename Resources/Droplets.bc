define i32 @foo(i32* %in, i32* %in2) {
	%s1 = load i32, i32* %in
	%s2 = load i32, i32* %in2
	%s3 = add i32 %s1, 4
	%s4 = add i32 %s2, 3
	%s5 = add i32 %s2, 2
	%s6 = add i32 %s1, %s3
	%s7 = add i32 %s2, %s5
	%s8 = add i32 %s6, 2
	%s9 = add i32 %s4, %s7
	ret i32 %s9
}

define i32 @main() {
	%1 = alloca i32, align 4
	store i32 4, i32* %1
	%2 = load i32, i32* %1
	%3 = sub i32 %2, %2
	call i32 @foo(i32* %1, i32* %1)
	
	ret i32 0
}