define i32 @foo(i32* %in, i32* %in2) {
	%s1 = load i32, i32* %in
	%s2 = load i32, i32* %in2
	%s3 = mul i32 %s1, 2
	%s4 = add i32 %s1, %s3
	%s5 = mul i32 %s2, 1
	%s6 = add i32 %s5, 3
	%s7 = sub i32 %s4, 1
	%s8 = add i32 %s5, %s6
	%s9 = add i32 %s7, %s8
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