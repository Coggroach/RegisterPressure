define i32 @foo(i32* %in, i32* %in2) {
	%s1 = load i32, i32* %in	
	%s2 = load i32, i32* %in2
	%s3 = add i32 %s1, 2
	%s4 = add i32 %s1, %s2
	%s5 = mul i32 %s2, 5
	%s6 = add i32 %s3, 1
	%s7 = sub i32 %s3, 1	
	%s8 = add i32 %s4, %s5
	%s9 = add i32 %s5, 10
	%s10 = add i32 %s6, %s7
	%s11 = add i32 %s8, 3
	%s12 = add i32 %s10, %s11
	%s13 = add i32 %s9, %s11
	%s14 = sub i32 %s13, %s12
	ret i32 %s14
}

define i32 @main() {
	%1 = alloca i32, align 4
	store i32 4, i32* %1
	%2 = load i32, i32* %1
	%3 = sub i32 %2, %2
	call i32 @foo(i32* %1, i32* %1)
	
	ret i32 0
}