/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:24:46 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/15 19:24:46 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 3, 5, 7, 9};
    int target = 4;

    auto it = std::upper_bound(numbers.begin(), numbers.end(), target);

    if (it != numbers.end()) {
        int result = *it;
        std::cout << "The first number greater than " << target << " is: " << result << std::endl;
    } else {
        std::cout << "No number greater than " << target << " found." << std::endl;
    }

    return 0;
}