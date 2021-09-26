/**\~russian @authors Золотов Сергей
 * \~russian @version 0.1
 * \~russian @date 12 марта 2021
 *
 * \~russian @brief Набор функций для создания и размещения в мире
 * тормозных мишеней простой формы.
 * */
#ifndef __Z6CREATEBTARGET_HH__
#define __Z6CREATEBTARGET_HH__

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4String.hh"
#include "G4Material.hh"

/**\~russian @brief Создаёт тормозную мишень в виде пластинки заданых параметров.
 *
 * \~russian @param [in] _target_name Имя создаваемой мишени
 * \~russian @param [in] _taget_size_x Размер (полный) пластинки по оси OX
 * \~russian @param [in] _taget_size_y Размер (полный) пластинки по оси OY
 * \~russian @param [in] _taget_size_z Размер (полный) пластинки по оси OZ
 * \~russian @param [in] _target_material Материал мишени
 * \~russian @param [in] _translation Координаты центра пластинки
 * \~russian @param [in] _mother_volume Указатель на материнский объём
 *
 * \~russian @todo Перегрузка с translation + rotation
 * \~russian @todo Перегрузка с G4Transform3D
 * */
G4PVPlacement* Z6CreateBTarget(
    const        G4String& _target_name,
    const         G4double _target_size_x,
    const         G4double _target_size_y,
    const         G4double _target_size_z,
               G4Material* _target_material,
    const   G4ThreeVector& _translation,
          G4LogicalVolume* _mother_volume
)
{
    G4Box* _solid = new G4Box(_target_name,
                              _target_size_x / 2,
                              _target_size_y / 2,
                              _target_size_z / 2);

    G4LogicalVolume* _logical = new G4LogicalVolume(_solid,
                                                    _target_material,
                                                    _target_name);

    return new G4PVPlacement(0,                     //no rotation
                             _translation,       //at (0,0,0)
                             _logical,            //its logical volume
                             _target_name,               //its name
                             _mother_volume,                     //its mother  volume
                             false,                 //no boolean operation
                             0,                     //copy number
                             true);                //overlaps checking
}

#endif
