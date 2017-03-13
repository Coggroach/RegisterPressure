define i32 @foo(i32* %in) {
	%s1 = load i32, i32* %in
	%s2 = add i32 %s1, 4
	%s3 = mul i32 %s1, 2
	%s4 = add i32 %s3, 1
	%s5 = mul i32 %s2, 2
	%s6 = add i32 %s3, %s4
	%s7 = sub i32 %s4, 1
	%s8 = add i32 %s5, 1
	%s9 = add i32 %s6, %s7
	%s10 = add i32 %s8, %s9
	ret i32 %s10
}

define i32 @main() {
	%1 = alloca i32, align 4
	store i32 4, i32* %1
	%2 = load i32, i32* %1
	%3 = sub i32 %2, %2
	call i32 @foo(i32* %1)
	
	ret i32 0
}