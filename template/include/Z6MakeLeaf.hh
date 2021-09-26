/**\~russian @authors Золотов Сергей
 * \~russian @version 0.1
 * \~russian @date 12 марта 2021
 *
 * \~russian @brief Набор функций для создания и размещения в мире
 * тормозных мишеней простой формы.
 * */
#ifndef __Z6MAKELEAF_HH__
#define __Z6MAKELEAF_HH__

#include "HyperParameters.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

/**\~russian @brief Создаёт лепесток коллиматора 77 х 10 х 0 мм
 * из вольфрама
 *
 * \~russian @param [in] _target_material Материал мишени
 * \~russian @param [in] _translation Координаты центра пластинки
 * \~russian @param [in] _mother_volume Указатель на материнский объём
 *
 * \~russian @todo Перегрузка с translation + rotation
 * \~russian @todo Перегрузка с G4Transform3D
 * */
void MakeLeaf(
    const   G4ThreeVector& _translation,
          G4LogicalVolume* _mother_volume
)
{
    // == == == == == == == == == == == == == == == == == == ==
    //
    static G4int copyNo = 0;
    static const G4bool overlapsChecking = true;

    // == == == == == == == == == == == == == == == == == == ==
    //
    static G4Box* _solid = new G4Box("__leaf",
                                     leaf_size_x / 2,
                                     leaf_size_y / 2,
                                     leaf_size_z / 2);

    static G4LogicalVolume* _logical = new G4LogicalVolume(_solid,
                                                           leaf_material,
                                                           "__leaf");

    new G4PVPlacement(0,                    // no rotation
                      _translation,         // its translation
                      _logical,             // its logical volume
                      "__leaf",             // its name
                      _mother_volume,       // its mother  volume
                      false,                // no boolean operation
                      copyNo,               // copy number
                      overlapsChecking);    // overlaps checking

    ++copyNo;
}

#endif
