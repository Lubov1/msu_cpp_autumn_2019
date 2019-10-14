import subprocess
def check(expr,result):
	out = subprocess.run(['./calc',expr],stdout=subprocess.PIPE)
	if out.stdout.decode('ascii')!=result:
		print('error {0}!={1},got{2}'.format(expr,result,out.stdout))


check('2+2','4')
check('2*9','18')
check('22/2*-1 +10*2     -55','-46')
check('22/2--1 +10*2','32')
check('50/5*9--2-3/3+10','101')
check('2-45/9','-3')
check('7','7')
check('8+-6','2')


