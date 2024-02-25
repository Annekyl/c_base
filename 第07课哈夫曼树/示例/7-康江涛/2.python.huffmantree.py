import turtle

class Node:
    def __init__(self, num, left, right, parent):
        self.num = num
        self.left = left
        self.right = right
        self.parent = parent

def input_nums():
    nums = []
    length = 0
    while True:
        num = int(input())
        nums.append(num)
        length += 1
        if num == 0:
            break
    return nums, length

def output_nums(nums):
    for num in nums:
        print(num, end=' ')
    print()

def bubble_sort(nums):
    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            if nums[i] > nums[j]:
                nums[i], nums[j] = nums[j], nums[i]
    output_nums(nums)

def create_node(num, left, right, parent):
    return Node(num, left, right, parent)

def print_node(node):
    print(f"num: {node.num}, left: {node.left}, right: {node.right}, parent: {node.parent}")

def create_huffman_tree(nums, length,ps):
    # 创建n个只有一个num的二叉树
    for i in range(1, length):
        ps[i-1] = create_node(nums[i], 0, 0, 0)
    
    # 创建新的节点
    ps[length-1] = create_node(nums[1] + nums[2], nums[1], nums[2], nums[2+3] + nums[1] + nums[2])
    ps[length] = create_node(nums[3] + nums[4], nums[3], nums[4], nums[3] + nums[4] + nums[4+2])

    for i in range(length+1, 2*length-6):
        j = i - length - 1
        current_num = nums[j+5] + ps[i-2].num
        if (i-length+1) % 2 == 0:
            current_left = ps[i-2].num
            current_right = nums[j+5]
        else:
            current_right = ps[i-2].num
            current_left = nums[j+5]
        current_parent = current_num + nums[j+2+5]
        ps[i] = create_node(current_num, current_left, current_right, current_parent)
    
    # 最后三个节点
    for i in range(2*length-6,2*length-4):
        j=i - length - 1
        current_num=nums[j+5] + ps[i-2].num
        if (i-length+1) % 2 == 0:
            current_left = ps[i-2].num
            current_right = nums[j+5]
        else:
            current_right = ps[i-2].num
            current_left = nums[j+5]
        ps[i] = create_node(current_num, current_left, current_right,0)
    ps[2*length-6].parent = ps[2*length-6].num + ps[2*length-5].num
    ps[2*length-5].parent = ps[2*length-6].num + ps[2*length-5].num
    ps[2*length-4] = create_node(ps[2*length-6].num + ps[2*length-5].num, ps[2*length-6].num, ps[2*length-5].num, 0)

def one_circle(num,x,y):
    turtle.tracer(False)
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.circle(30)
    turtle.penup()
    turtle.goto(x-10, y+10)
    turtle.write(str(num), font=("Arial", 15, "normal"))
    turtle.tracer(True)

def draw_huffman_tree(ps,length):
    # 首先先画出第一个节点 # 最后一个节点是2*length-4 第一个节点就是length-1
    one_circle(ps[0].num,0,300)
    one_circle(ps[0].left,-120,300-60)
    one_circle(ps[0].right,120,300-60)
    for i in range(1,length):
        if((i+1)%2 != 0): #单数在左 偶数在右
            one_circle(ps[i].left,-120-(60*(i+1)/2-1),240-i*60)
            one_circle(ps[i].right,-120-(60*(i+1)/2-1)+120,240-i*60)
        else:
            one_circle(ps[i].left,120+(60*(i/2-1)),240-(i+1)*60)
            one_circle(ps[i].right,120+(60*(i/2-1))+120,240-(i+1)*60)
    

def main():
    nums, length = input_nums()
    output_nums(nums)
    bubble_sort(nums)
    ps = [None] * (2 * length - 1) # 这个用来装每一个节点
    create_huffman_tree(nums, length,ps)
    ps_now=[None] * (2*length-4-length+2)
    j=0
    for i in range(2*length-4, length-2, -1):
        ps_now[j] = ps[i]
        j+=1
    for i in range(0,2*length-4-length+2):
        print_node(ps_now[i])
    length = 2*length-4-length+2
    draw_huffman_tree(ps_now,length)
    turtle.hideturtle()
    turtle.done()
        
main()


